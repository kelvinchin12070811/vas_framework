/** @page extlibs Required external libraries
	  
The vas_framework riquired some external libraries to complie bellow are the compleate list of them.

@note The term "Global inclue path" is refer to the compiler's global include path which are able to locate with
"#include <>".

## Required Library
These is the libraries that core component of vas_framework required:
<table>
	<tr>
		<th>Library</th>
		<th>Required version</th>
		<th>Requied files</th>
		<th>Additional requirement</th>
	</tr>
	<tr>
		<td>[Boost C++ library](http://www.boost.org)</td>
		<td>1.67.0 +</td>
		<td>"boost" folder under the root dir, config as gloal include path.</td>
		<td>Compiled are not needed.</td>
	</tr>
	<tr>
		<td>[SDL2](http://www.libsdl.org)</td>
		<td>2.0.7 +</td>
		<td>Global include path to "include" folder.</td>
		<td>none</td>
	</tr>
	<tr>
		<td>[SDL_image](http://www.libsdl.org/projects/sdl_image)</td>
		<td>2.0.2 +</td>
		<td>Global include path to "include" folder.</td>
		<td>none</td>
	</tr>
</table>

## Optional Library
These libraries are optional and the library will disable the components that required them.
<table>
	<tr>
		<th>Library</th>
		<th>Required version</th>
		<th>Required by component</th>
		<th>Required files</th>
		<th>Additinoal requirement</th>
	</tr>
	<tr>
		<td>[pugixml](http://pugixml.org/)</td>
		<td>1.9 +</td>
		<td>Tiled TMX parser</td>
		<td>Global include path to "src" folder.</td>
		<td>
			The library must be in eighter header only mode or compiled into static library. Include it under project source
			directory will not work.
		</td>
	</tr>
	<tr>
		<td>[rapidjson](http://www.rapidjson.org)</td>
		<td>1.1.0 +</td>
		<td>NBT tags Json serializer & desirializer</td>
		<td>Global include path to "include" folder.</td>
		<td>none</td>
	</tr>
	<tr>
		<td>[SDL_mixer](http://www.libsdl.org/projects/sdl_mixer)</td>
		<td>2.0.2 +</td>
		<td>Audio component</td>
		<td>Global include path to "include" folder.</td>
		<td>none</td>
	</tr>
	<tr>
		<td>[SDL_TTF](http://www.libsdl.org/projects/sdl_ttf)</td>
		<td>2.0.14 +</td>
		<td>Text rendereing component</td>
		<td>Global include path to "include" folder.</td>
		<td>none</td>
	</tr>
	<tr>
		<td>[zlib](http://www.gzip.org/zlib/)</td>
		<td>1.2.8 +</td>
		<td>Tiled TMX parser</td>
		<td>Global include path to "include" folder.</td>
		<td>none</td>
	</tr>
	<tr>
		<td>[Box2D](http://www.box2d.org)</td>
		<td>2.3.1+</td>
		<td>Box2D folder under root/Box2D, as global path.</td>
		<td>none</td>
	</tr>
</table>

## Other Bundled Libraries

 - [ReneNyffenegger's base64](https://github.com/ReneNyffenegger/cpp-base64)

 ## About Third-parties Notices
 
 All of the licenses used by Virtual Assistance Framework are placed at the "3rd_party_notices.zip" file under the
 project root directory.
*/