#define _EXIT_  4
#include "app_main_framework.hpp"
#include "fstream_guard.hxx"
#include <cstring>
#include <iostream>
#include <source/include/public/FE.utility.singleton.hxx>


bool amf::g_is_main_loop_active = true;


int amf::get_message() noexcept
{
	system("cls");
	std::cout << "Current play list:" << std::endl;

	for (FE::fstring<_FSTRING_LENGTH_>& ref : FE::utility::singleton<music_play_list>::singleton_instance()._song_list)
	{
		if (ref[0] != '\0')
		{
			std::cout << ref.c_str() << std::endl;
		}
	}
	std::cout << std::endl
		<< "Select one of these actions below:" << std::endl
		<< "1. Play a song" << std::endl
		<< "2. Add a song to the play list" << std::endl
		<< "3. Remove a song from the play list" << std::endl
		<< "4. Shut Off" << std::endl <<std::endl
		<< "Input a number [e.g. 1~4]: ";
	char l_input_buffer = 0;
	std::cin >> l_input_buffer;
	std::cin.ignore();
	return FE::algorithm::string::char_to_int<char, int>(l_input_buffer);
}


void amf::playing_action::take_action() noexcept
{
	system("cls");
	std::cout << "Playing music..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Failed to play the song. You have not purchased the premium subscription." << std::endl;
	system("cls");
}

void amf::adding_action::take_action() noexcept
{
	FE::fstring<_FSTRING_LENGTH_> l_input_buffer; 

	do
	{
		system("cls");
		FE::memory::memset_s(l_input_buffer.begin(), 0, _FSTRING_LENGTH_, sizeof(FE::fstring<_FSTRING_LENGTH_>::char_t));

		std::cout << " \"2. Add a song to the play list\" has been selected."
			<< "Input the name of song and the artist [e.g. artist - song title]: ";
		std::cin.getline(l_input_buffer.begin(), _FSTRING_LENGTH_);
	} while (FE::algorithm::string::find_a_character(l_input_buffer.c_str(), '-').second != '-');


	FE::fstring<_FSTRING_LENGTH_> l_final_string_buffer;


	FE::var::uint64 l_song_index = 1;
	for (FE::fstring<_FSTRING_LENGTH_>& ref : FE::utility::singleton<music_play_list>::singleton_instance()._song_list)
	{
		if (ref[0] != '\0')
		{
			++l_song_index;
		}
	}

	snprintf(l_final_string_buffer.begin(), 
			_FSTRING_LENGTH_, 
			"%d", 
			l_song_index
			);
	
	FE::algorithm::string::strcat<FE::fstring<_FSTRING_LENGTH_>::char_t>(l_final_string_buffer.begin(), 
																		_FSTRING_LENGTH_, 
																		const_cast<char*>(". "), 
																		3);

	FE::algorithm::string::strcat<FE::fstring<_FSTRING_LENGTH_>::char_t>(l_final_string_buffer.begin(), 
																		_FSTRING_LENGTH_, 
																		l_input_buffer.begin(), 
																		FE::algorithm::string::strlen<FE::fstring<_FSTRING_LENGTH_>::char_t>(l_input_buffer.c_str()) 
																		);

	FE::utility::singleton<music_play_list>::singleton_instance()._song_list.emplace_back(l_final_string_buffer);


	std::ofstream l_file_writter;
	IO::write_file(l_file_writter, "my_music_play_list.playlist", FE::utility::singleton<music_play_list>::singleton_instance()._song_list );
}

void amf::deleting_action::take_action() noexcept
{
	char l_input_buffer = '\0';
	do
	{
		system("cls");
		l_input_buffer = '\0';

		std::cout << " \"3. Remove a song from the play list\" has been selected."
			<< "Input the code of the song that you want to delete from the play list: ";
		std::cin >> l_input_buffer;
		std::cin.ignore();
	} while (FE::algorithm::string::char_to_int<char, FE::var::uint64>(l_input_buffer) > FE::utility::singleton<music_play_list>::singleton_instance()._song_list.size());


	auto l_new_begin = FE::utility::singleton<music_play_list>::singleton_instance()._song_list.begin();
	auto l_end = FE::utility::singleton<music_play_list>::singleton_instance()._song_list.end();

	if ((*l_new_begin)[0] == '\0') 
	{
		system("cls");
		std::cout << "The list is empty" << std::endl;
		return; 
	}

	for (; l_new_begin < l_end; ++l_new_begin)
	{
		if ((*l_new_begin)[0] == l_input_buffer)
		{
			FE::memory::memset_s((*l_new_begin).begin(), 0, _FSTRING_LENGTH_, sizeof(FE::fstring<_FSTRING_LENGTH_>::char_t));
		}
		else if ((*l_new_begin)[0] != ' ' && (*l_new_begin)[0] > l_input_buffer)
		{
			--(*l_new_begin)[0];
		}
	}

	std::ofstream l_file_writter;
	IO::write_file(l_file_writter, "my_music_play_list.playlist", FE::utility::singleton<music_play_list>::singleton_instance()._song_list);
}

void amf::exit_action::take_action() noexcept
{
	g_is_main_loop_active = false;
	std::cout << std::endl << "Terminating the application process. Thanks!" << std::endl;
}



amf::action_base* amf::interpret_input_code(const int input_p) noexcept
{
	static playing_action l_s_playing_action;
	static adding_action l_s_adding_action;
	static deleting_action l_s_deleting_action;
	static exit_action l_s_exit_action;
	static idle_action l_s_idle_action;

	switch (input_p)
	{
	case 1:
		return &l_s_playing_action;

	case 2:
		return &l_s_adding_action;

	case 3:
		return &l_s_deleting_action;

	case 4:
		return &l_s_exit_action;

	default:
		return &l_s_idle_action;
		break;
	}
}

void amf::idle_action::take_action() noexcept
{
}
