#ifndef _FSTREAM_GUARD_HXX_
#define _FSTREAM_GUARD_HXX_
#include <fstream>


namespace io
{
	template<class fstream>
	class fstream_guard
	{
		fstream& m_file_io_ref;

	public:
		fstream_guard(fstream& file_io_ref_p) noexcept : m_file_io_ref(file_io_ref_p) {}

		fstream_guard(fstream& file_io_ref_p, const char* cstr_ptr_p) noexcept : m_file_io_ref(file_io_ref_p) 
		{
			if (m_file_io_ref.is_open() == false)
			{
				m_file_io_ref.open(cstr_ptr_p);
			}
		}

		fstream_guard(fstream& file_io_ref_p, const wchar_t* cwstr_ptr_p) noexcept : m_file_io_ref(file_io_ref_p)
		{
			if (m_file_io_ref.is_open() == false)
			{
				m_file_io_ref.open(cstr_ptr_p);
			}
		}

		~fstream_guard() noexcept 
		{
			if (this->m_file_io_ref.is_open() == true)
			{
				this->m_file_io_ref.close();
			}
		}

		bool is_open() noexcept
		{
			return this->m_file_io_ref.is_open();
		}
	};


	template<typename char_type, class container>
	void write_file(std::basic_ofstream<char_type, std::char_traits<char_type>>& file_writter_p, const char_type* filename_ptr_p, container& container_p) noexcept
	{
		io::fstream_guard<std::ofstream> l_file_writter_guard(file_writter_p, filename_ptr_p);
		for (auto& ref : container_p)
		{
			if (ref[0] != static_cast<char_type>('\0'))
			{
				file_writter_p << ref.c_str() << std::endl;
			}
		}
	}
}

#endif // !_FSTREAM_GUARD_HXX_
