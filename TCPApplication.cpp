#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>

namespace opts = boost::program_options;

constexpr unsigned short MIN_NONPRIVILEGED_PORT = 1024;

namespace
{
bool Validate(const opts::variables_map &vm)
{
    bool bValid = true;
    if ((vm.count("client") > 0) && (vm.count("server") > 0))
    {
        bValid = false;
        std::cerr << "Cannot start both server and client. " << std::endl;
    }

    if ((vm.count("client") == 0) && (vm.count("server") == 0))
    {
        bValid = false;
        std::cerr << "Please start either server or client. " << std::endl;
    }

    const unsigned short port = vm["port"].as<unsigned short>();
    if (port < 1024)
    {
        bValid = false;
        std::cerr << "Cannot start server with port less than 1024. Value "
                     "provided: "
                  << port << std::endl;
    }
    return bValid;
}
} // namespace

extern void StartServer(unsigned short port);
extern void StartClient(unsigned short port);

int main(int argc, char **argv)
{
    unsigned short port;
    opts::options_description options;
    // clang-format off
    options.add_options()
	   ("server", "Start server")
	   ("client", "Start client")
	   ("help", "usage")
	   ("port", opts::value<unsigned short>(&port)->default_value(MIN_NONPRIVILEGED_PORT + 1), "Server port")
	   ;
    // clang-format on

    opts::variables_map vm;
    opts::store(opts::parse_command_line(argc, argv, options), vm);
    opts::notify(vm);

    if (!Validate(vm))
    {
        return -1;
    }

	if (vm.count("server"))
	{
		StartServer(port);
	}
	else
	{
		StartClient(port);
	}

    return 0;
}
