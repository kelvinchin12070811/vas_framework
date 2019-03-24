/**
 * @page component_cast_exp SDL Component Casting Example
 * 
 * ~~~cpp
 * sdl::Window firstWin("Test Widow", sdl::Point(640, 480), sdl::Window::Flags::shown);
 * 
 * //Cast to raw component.
 * SDL_Window* rawComp = static_cast<SDL_Window*>(firstWin);
 * 
 * //Cast to wrapped component. note the casted component is a weak reference of component (does not destroy after out of scope).
 * sdl::Window win = static_cast<sdl::Window>();
 * ~~~
 */