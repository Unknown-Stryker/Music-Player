#include "application_initializer.hpp"
#include "fstream_guard.hxx"
#include "music_play_list.hpp"
#include <source/private/runtime_exception.cpp>
#include <source/private/parallel.mutex.cpp>
#include <source/private/utility.clock.cpp>
#include <fstream>
#include <iostream>
#include <cstring>


void IO::initialize_app() noexcept
{
	std::ifstream l_play_list_reader;
	IO::fstream_guard<std::ifstream> l_play_list_reader_guard(l_play_list_reader, "my_music_play_list.playlist");

	if (l_play_list_reader_guard.is_open() == false)
	{
		char l_buffer = '\0';
		do
		{
			std::cout << "Failed to load a music play list save file.\nDo you want to add default songs to your play list?\n[Y/N]: ";
			std::cin >> l_buffer;
			if (l_buffer == 'Y' || l_buffer == 'y')
			{
				FE::utility::singleton<music_play_list>::singleton_instance()._song_list.emplace_back("1. Adele - Rolling in the Deep");
				FE::utility::singleton<music_play_list>::singleton_instance()._song_list.emplace_back("2. Ed Sheeran - Shape of You");
				FE::utility::singleton<music_play_list>::singleton_instance()._song_list.emplace_back("3. Dua Lipa - Don't Start Now");
				FE::utility::singleton<music_play_list>::singleton_instance()._song_list.emplace_back("4. The Weeknd - Blinding Lights");
				FE::utility::singleton<music_play_list>::singleton_instance()._song_list.emplace_back("5. Lady Gaga - Bad Romance");
				FE::utility::singleton<music_play_list>::singleton_instance()._song_list.emplace_back("6. Bruno Mars - Uptown Funk");
			}
			system("cls");
		} while (l_buffer != 'Y' && l_buffer != 'N' && 
				 l_buffer != 'y' && l_buffer != 'n');

		std::ofstream l_file_creator;
		IO::write_file(l_file_creator, "my_music_play_list.playlist", FE::utility::singleton<music_play_list>::singleton_instance()._song_list);
		return;
	}

	FE::fstring<_FSTRING_LENGTH_> l_string_buffer;
	while (l_play_list_reader)
	{
		l_play_list_reader.getline(l_string_buffer.begin(), l_string_buffer.capacity());
		if (l_string_buffer[0] != ' ')
		{
			FE::utility::singleton<music_play_list>::singleton_instance()._song_list.emplace_back(l_string_buffer);
		}
	}
}
