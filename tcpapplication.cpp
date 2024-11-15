#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>

namespace opts = boost::program_options;

constexpr int MIN_NONPRIVILEGED_PORT = 1024;

namespace
{
bool Validate(const opts::variables_map &vm)
{
    bool bValid = true;
    if ((vm.count("client") > 0) && (vm.count("server") > 0))
    {
        bValid = false;
        std::cerr << "Please start either the server or client. " << std::endl;
    }

    const int port = vm["port"].as<int>();
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

int main(int argc, char **argv)
{
    int port;
    opts::options_description options;
    // clang-format off
    options.add_options()
	   ("server", "Start server")
	   ("client", "Start client")
	   ("help", "usage")
	   ("port", opts::value<int>(&port)->default_value(MIN_NONPRIVILEGED_PORT + 1), "Server port")
	   ;
    // clang-format on

    opts::variables_map vm;
    opts::store(opts::parse_command_line(argc, argv, options), vm);
    opts::notify(vm);

    if (!Validate(vm))
    {
        return -1;
    }

    // Create server or client as needed

    return 0;
}
