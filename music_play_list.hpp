#ifndef _MUSIC_PLAY_LIST_HPP_
#define _MUSIC_PLAY_LIST_HPP_
#define _LIST_RESERVATION_SIZE_ 100
#define _FSTRING_LENGTH_ 100
#include <source/include/public/FE.memory.fstring.hxx>
#include <source/include/public/FE.utility.singleton.hxx>
#include <vector>


struct music_play_list
{
	FRIEND_CLASS_SINGLETON(music_play_list);

	std::vector<FE::fstring<_FSTRING_LENGTH_>> _song_list;

private:
	music_play_list() noexcept 
	{
		this->_song_list.reserve(_LIST_RESERVATION_SIZE_);
	}
};
#undef _LIST_RESERVATION_SIZE_
#endif