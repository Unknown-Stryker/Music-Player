// Copyright © 2023 by UNKNOWN STRYKER. All Rights Reserved.
#include "application_initializer.hpp"
#include "app_main_framework.hpp"



int main(void)
{
	IO::initialize_app();

	int l_input_result = 0;

	while (amf::g_is_main_loop_active == true)
	{
		l_input_result = amf::get_message();
		amf::interpret_input_code(l_input_result)->take_action();
	}

	return 0;
}