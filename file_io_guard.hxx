#ifndef _FILE_IO_GUARD_HXX_
#define _FILE_IO_GUARD_HXX_


namespace IO
{
	template<class FILE_IO>
	class file_io_guard
	{
		FILE_IO& m_file_io_ref;

	public:
		file_io_guard(FILE_IO& file_io_ref_p) noexcept : m_file_io_ref(file_io_ref_p) {}

		file_io_guard(FILE_IO& file_io_ref_p, const char* cstr_ptr_p) noexcept : m_file_io_ref(file_io_ref_p) 
		{
			if (m_file_io_ref.is_open() == false)
			{
				m_file_io_ref.open(cstr_ptr_p);
			}
		}

		file_io_guard(FILE_IO& file_io_ref_p, const wchar_t* cwstr_ptr_p) noexcept : m_file_io_ref(file_io_ref_p)
		{
			if (m_file_io_ref.is_open() == false)
			{
				m_file_io_ref.open(cstr_ptr_p);
			}
		}

		~file_io_guard() noexcept 
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
}

#endif // !_FILE_IO_GUARD_HXX_
