#include <iostream>

#include <nlohmann/json.hpp>

#include "httplib.h"


void invalid_name ( std::string *page ) {
	*page = "5555";

	std::cout << "Unsupported page name\n";
	std::cout << "Using default name: <55555>\n";
}

int post_count;

int main ( ) {
	httplib::Server server;

	setlocale ( LC_ALL, "RUS" );

	std::cout << "ѕривет, защита сервера это сложна€ часть.\n";
	std::cout << "јтака API запросов одна из самых распространенных.\n";
	std::cout << "—амый простой способ защитить бекенд - маскировка.\n";
	std::cout << "ƒавай придумаем название дл€ нашего запроса к базе данных.\n";
	std::cout << "ƒл€ ускорени€ процесса, будем использовать INT(11111-99999).\n";
	std::cout << "ѕодумай, какое название будет самым правильным.\n";
	std::cout << "Ѕери во внимание возможные переборы.\n";
	std::cout << " ак будет называтьс€ наш запрос?\n->";


	std::string page;
	std::cin >> page;

	post_count = 0;


	for ( const char &ch : page ) {
		if ( ch < '0' || ch > '9' ) {
			invalid_name ( &page );
			break;
		}
	}


	if ( page.length ( ) != 5 ) {
		invalid_name ( &page );
	}


	server.Get ( "/" + page, []( const httplib::Request &request, httplib::Response &response ) {
		nlohmann::json js;

		if ( request.has_param ( "request" ) ) {
			js ["status"] = "POST.OK";
			js ["return"] = "EXECUTION.OK";

			if ( ++post_count >= 500 ) {
				js ["status"] = "ERR.FLAG_1234";
				js ["return"] = "EXECUTION.UNAVAILABLE";
			}
		}
		else {
			js ["status"] = "POST.BAD";
		}

		response.set_content ( js.dump ( ), "application/json" );
	} );


	std::string host = "localhost";
	int port = 8080;

	server.listen ( host, port );
}