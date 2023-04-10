#include "application_initializer.hpp"
#include "music_play_list.hpp"
#include <Frogman-API-Lab/source/private/runtime_exception.cpp> // #including .cpp files will be replaced with a DLL or a static library in later versions.
#include <Frogman-API-Lab/source/private/parallel.mutex.cpp>
#include <Frogman-API-Lab/source/private/utility.clock.cpp> 
#include <Frogman-API-Lab/source/include/public/FE.utility.fstream_guard.hxx>
#include <fstream>
#include <iostream>
#include <cstring>


void io::initialize_app() noexcept
{
	std::ifstream l_play_list_reader;
	FE::ifstream_guard l_play_list_reader_guard(l_play_list_reader, "my_music_play_list.playlist");

	if (l_play_list_reader_guard.is_open() == false)
	{
		FE::fstring<_FSTRING_LENGTH_>::char_t l_buffer = '\0';
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
		FE::ofstream_guard l_ofstream_guard(l_file_creator, "my_music_play_list.playlist");
		l_ofstream_guard.write_a_file(FE::utility::singleton<music_play_list>::singleton_instance()._song_list);
		return;
	}

	l_play_list_reader_guard.read_a_file<std::vector<FE::fstring<_FSTRING_LENGTH_>>, _FSTRING_LENGTH_>( FE::utility::singleton<music_play_list>::singleton_instance()._song_list );
}
