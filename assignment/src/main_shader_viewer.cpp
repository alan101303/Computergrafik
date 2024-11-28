#ifdef _WIN32
#  include <windows.h>
#  include <stdlib.h>
#  include <errhandlingapi.h>
#endif


#include "render/ShaderViewer.h"
#include <vector>
#include <string>

std::string const shader_path(SHADER_PATH);

int main(int argc, char *argv[])
{
#ifdef _WIN32
    // This make crashes very visible - without them, starting the
    // application from cmd.exe or powershell can surprisingly hide
    // any signs of a an application crash!
    SetErrorMode(0);
#endif
	
	if(argc < 2) {
		std::cerr << "Usage:\n";
        std::cerr << "    " << argv[0] << "my_shader.frag\n";
        std::cerr << "  or\n";
        std::cerr << "    " << argv[0] << "my_shader.frag output.png\n\n";
		std::cerr << "Shader directory: " << shader_path << std::endl;
		return 1;
	}

	std::string out_file_path;
	if(argc >= 3) {
		// 2nd argument is the file to write
		out_file_path = argv[2];
	}
	
	std::vector<std::string> my_frag_shaders = {
		shader_path + "/noise.frag",
		shader_path + "/" + argv[1]
	};

	ShaderViewer shvi;
	shvi.setShaderFiles({shader_path + "/display.vert"}, my_frag_shaders);
	//shvi.run(out_file_path);
	shvi.run([&]() {
		if(!out_file_path.empty()) {
			shvi.saveScreenshot(out_file_path);
		}
		return true;
	});
}
