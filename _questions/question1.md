I've got a bug with my OpenGL program and I'm totally stumped at whats causing it.

I have a Cube class that initalizes a VAO and VBOs for its vertices and UV coords. It also has a Render function that sets the Vertex Attribute Pointers and draws the arrays.

When I init cube normally it works fine:
```c++
Cube cube("res/uvtemplate.bmp", 1.0f, 0.0f, 0.0f); // last 3 floats are world pos
cube.Init(shader.getProgramId()); // gets uniform location of texture sampler for shader
// ... within render loop
cube.Rander(/*MVP stuff*/);
```



**BUT** when I initialize a cube object within a vector<Cube> things go tits up.
```c++
std::vector<Cube> cubes;
cubes.push_back(Cube("res/uvtemplate.bmp", 0.0f, -4.0f, 0.0f));
cubes[0].Init(shader.getProgramID());
// .. within render loop ...
cubes[0].Render(/*MVP stuff*/);
```


Yeah, you delete the buffers on copy, that's going to break.
You probably want to delete the copy-constructor and implement a move constructor, or better, use unique_ptrs for the buffers with a custom deleter.
@Peter in general, when writing a class, you wanna decide whether the thing should be copy or moveable and, if not, delete the copy ctor and assignment op right away


