#ifndef _APP_MAIN_FRAMEWORK_HPP_
#define _APP_MAIN_FRAMEWORK_HPP_
#include "music_play_list.hpp"


namespace amf // app main framework
{
	extern bool g_is_main_loop_active;


	int get_message() noexcept;


	class action_base
	{
	public:
		virtual void execute() noexcept = 0;
	};

	class playing_action : public action_base
	{
	public:
		virtual void execute() noexcept override;
	};

	class adding_action : public action_base
	{
	public:
		virtual void execute() noexcept override;
	};

	class deleting_action : public action_base
	{
	public:
		virtual void execute() noexcept override;
	};

	class exit_action : public action_base
	{
	public:
		virtual void execute() noexcept override;
	};

	class idle_action : public action_base
	{
	public:
		virtual void execute() noexcept override;
	};

	action_base* interpret_input_code(const int input_p) noexcept;
}

#endif // !_APP_FRAMEWORK_HPP_