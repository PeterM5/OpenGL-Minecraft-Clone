#include "texture.h"

Texture::Texture() {
}

Texture::Texture(const char * imagepath, GLuint programID) 
{
	if (loadImage(imagepath)) {
		Init(programID);
	}
}

// Create texture directly from RGB data
Texture::Texture(const unsigned char * RGB_buffer, const unsigned int width, const unsigned int height, GLuint programID)
	:m_image_size(width*height*3)
	,m_width(width)
	,m_height(height)
{
	// Create OpenGL Texture
	glGenTextures(1, &m_texture_id);

	// Give data to OpenGL Texture
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, RGB_buffer);

	Init(programID);
}

// Create texture from buffer of floats
Texture::Texture(const float * data_buffer, unsigned int db_length, const unsigned int width, const unsigned int height, GLuint programID)
	:m_image_size(width*height*3)
	,m_width(width)
	,m_height(height)
{
	if (m_image_size < db_length)
	{
		db_length = m_image_size;
	}
	unsigned char * RGB_buffer = new unsigned char[m_image_size*3];
	// Convert floats (ranging from 0.0f to 1.0f) to RGB values
	for (unsigned int i = 0; i < db_length; i++)
	{
		RGB_buffer[i*3] = data_buffer[i]*255;  // Red
		RGB_buffer[i*3+1] = data_buffer[i]*255;// Green
		RGB_buffer[i*3+2] = data_buffer[i]*255;// Blue
	}

	// Create OpenGL Texture
	glGenTextures(1, &m_texture_id);

	// Give data to OpenGL Texture
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, RGB_buffer);

	Init(programID);

}



void Texture::Init(GLuint programID)
{
		// nice trilinear filtering ...
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// ... which requires mipmaps. Generate them automatically.
		glGenerateMipmap(GL_TEXTURE_2D);

		m_uniform = glGetUniformLocation(programID, "textureSampler");
}

Texture::Texture(Texture && other)
	: m_texture_id(other.m_texture_id)
	, m_image_size(other.m_image_size)
	, m_width(other.m_width)
	, m_height(other.m_height)
	, m_uniform(other.m_uniform)
{
	// Reset to 0 so other's destructor doesnt delete our texture
	other.m_texture_id = 0;
}

Texture::~Texture() 
{
    glDeleteTextures(1, &m_texture_id);
}

bool Texture::loadImage(const char * imagepath) {
    switch (fileExtension(imagepath)) {
		case TEX_BMP:
			loadBMP(imagepath);
			return true;
			break;
		case TEX_DDS:
			loadDDS(imagepath);
			return true;
			break;
		default:
			printf("%s is an invalid file type for texture.\n", imagepath);
			return false;
	}
}

bool Texture::loadBMP(const char * imagepath) 
{
    printf("Reading image %s\n", imagepath);

    // Head data
	const unsigned int header_size = 122;
    unsigned char header[header_size];
    unsigned int dataPos;
    
    // Open file
    FILE * file = fopen(imagepath, "rb"); // Read Binary
    if (!file) {
        printf("%s could not be opened. Check if image path is correct.\n", imagepath);
        return false;
    }

    // Read the header
    // Less than 54 bytes where read. Problem.
    if (fread(header, 1, header_size, file) != header_size) {
        printf("%s is not a valid BPM file. Could not read.", imagepath);
        fclose(file);
        return false;
    }

    // A BPM file allways begins with "BM"
    if (header[0] != 'B' || header[1] != 'M') {
        printf("%s is not a valid BPM file. Could not read.", imagepath);
        fclose(file);
        return false;
    }

	// Make sure this is a 24bpp file
	if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    fclose(file); return false;}
	if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    fclose(file); return false;}

	// Read the information about the image
	dataPos    = *(int*)&(header[0x0A]);
	m_image_size  = *(int*)&(header[0x22]);
	m_width      = *(int*)&(header[0x12]);
	m_height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (m_image_size==0)    m_image_size=m_width*m_height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=header_size; // The BMP header is done that way

    // Create buffer for image in heap
	unsigned char* buffer;
    buffer = new unsigned char [m_image_size];

    // Read the image data from file to buffer
    fread(buffer, 1, m_image_size, file);

    // Read everything to memory, now we can close
    fclose(file);

	// Create OpenGL Texture
	glGenTextures(1, &m_texture_id);

	// Give data to OpenGL Texture
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, buffer);

	// OpenGL now has copied the data, we can free our stored version
	delete [] buffer;

    return true;
}

bool Texture::loadDDS(const char * imagepath) {
    
	unsigned char header[124];

	FILE *fp; 
 
	/* try to open the file */ 
	fp = fopen(imagepath, "rb"); 
	if (fp == NULL){
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar(); 
		return 0;
	}
   
	/* verify the type of file */ 
	char filecode[4]; 
	fread(filecode, 1, 4, fp); 
	if (strncmp(filecode, "DDS ", 4) != 0) { 
		fclose(fp); 
		return 0; 
	}
	
	/* get the surface desc */ 
	fread(&header, 124, 1, fp); 

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width	     = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);


	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */ 
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; // bufsize is twice as big if using mipmap: http://upload.wikimedia.org/wikipedia/commons/5/5c/MipMap_Example_STS101.jpg
	buffer = new unsigned char[bufsize * sizeof(unsigned char)];
	fread(buffer, 1, bufsize, fp); 
	/* close the file pointer */ 
	fclose(fp);

	//unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4; 
	unsigned int format;
	switch(fourCC) 
	{ 
	case FOURCC_DXT1: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
		break; 
	case FOURCC_DXT3: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
		break; 
	case FOURCC_DXT5: 
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
		break; 
	default: 
		delete[] buffer;
		return 0; 
	}

	// Create one OpenGL texture
	glGenTextures(1, &m_texture_id);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
	
	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
	unsigned int offset = 0;

	/* load the mipmaps */ 
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) 
	{ 
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
			0, size, buffer + offset); 
	 
		offset += size; 
		width  /= 2; 
		height /= 2; 

		// Deal with Non-Power-Of-Two textures.
		if(width < 1) width = 1;
		if(height < 1) height = 1;

	} 

	delete[] buffer;

	return true;
}

int Texture::fileExtension(const char * imagepath) const {
    // Locate extension
    int ext_pos = -1;
    long path_length = 0;

    // Get imagepath length
    while (imagepath[path_length] != '\0') { // End when we reach string escape char
        path_length++;
    }

    if (path_length == 0) { // Error no data given
        return 0;
    }

    // Obtain position in string of the extension delimiter (find position of last '.')
    for (int i = path_length-1; i > -1; i--) {
        if (imagepath[i] == '.') {
            ext_pos = i;
            break;
        }
    }
    if (ext_pos == -1) { // Error, no extension found
        return 0;
    }

    // copy extension section of string into a new string
    unsigned int ext_length = path_length - ext_pos;
    char ext[ext_length];
    std::copy(imagepath + ext_pos+1, imagepath + path_length, ext);
    ext[ext_length-1] = '\0'; // Set string delimeter

    // Convert imagepath extension to lower case
    for (unsigned int i=0; i<ext_length; i++) {
        if (ext[i] >= 'A' && ext[i] <= 'Z') {
            ext[i] = ext[i] + 32;
        }
    }

    if (!strcmp(ext, "bmp")) { // If equal, strcmp returns 0
        return TEX_BMP;
    }
    else if (!strcmp(ext, "dds")) {
        return TEX_DDS;
    }
    return 0;
}


GLuint Texture::getTextureID()
{
    return m_texture_id;
}

unsigned int Texture::getWidth() {
	return m_width;
}

unsigned int Texture::getHeight() {
	return m_height;
}

void Texture::bind()
{
    // Bind our terxture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    // Set our "textureSampler" sampler to use Texture Unit 0
    glUniform1i(m_uniform, 0);
}