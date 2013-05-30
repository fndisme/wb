/*
 * =====================================================================================
 *
 *       Filename:  DataBlock.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-12-22 10:26:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_MSG_SHIMS_DATABLOCK_H
#define FND_WEBGAME_MSG_SHIMS_DATABLOCK_H

#ifndef STLSOFT_INCL_STLSOFT_H_STLSOFT
# include <stlsoft/stlsoft.h>
#endif /* !STLSOFT_INCL_STLSOFT_H_STLSOFT */
#ifndef STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_STRING_H_FWD
# include <stlsoft/shims/access/string/fwd.h>
#endif /* !STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_STRING_H_FWD */
#ifndef STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_STRING_STD_H_C_STRING
# include <stlsoft/shims/access/string/std/c_string.h>
#endif /* !STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_STRING_STD_H_C_STRING */
#ifndef STLSOFT_INCL_STLSOFT_STRING_HPP_SHIM_STRING
# include <stlsoft/string/shim_string.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_SHIM_STRING */

#include "webgame/message/DataBlock.h"

namespace WebGame {
  namespace Message {
	inline stlsoft::basic_shim_string<stlsoft::ss_char_a_t>  c_str_data_a(
			const DataBlock* block) {
		typedef stlsoft::basic_shim_string<stlsoft::ss_char_a_t> shim_string_t ;
		if(block == NULL) {
			return shim_string_t(static_cast<shim_string_t::size_type>(0));
		}
		auto info = std::move(block->debugString()) ;
		return shim_string_t(info.c_str(), info.size()) ;
	}

	inline stlsoft::basic_shim_string<stlsoft::ss_char_a_t>  c_str_data(
			const DataBlock* block) {
		return c_str_data_a(block) ;
	}

	inline stlsoft::ss_size_t c_str_len_a(const DataBlock* block) {
		return block ? block->debugString().size() : 0 ;
	}

	inline stlsoft::ss_size_t c_str_len(const DataBlock* block) {
		return c_str_len_a(block) ;
	}

	inline stlsoft::basic_shim_string<stlsoft::ss_char_a_t> c_str_ptr_a(
			const DataBlock* block) {
		return c_str_data_a(block) ;
	}

	inline stlsoft::basic_shim_string<stlsoft::ss_char_a_t> c_str_ptr(
			const DataBlock* block) {
		return c_str_data_a(block) ;
	}

	inline stlsoft::basic_shim_string<stlsoft::ss_char_a_t> c_str_ptr_null_a(
			const DataBlock* block) {
		return c_str_data_a(block) ;
	}


	inline stlsoft::basic_shim_string<stlsoft::ss_char_a_t> c_str_ptr_null(
			const DataBlock* block) {
		return c_str_data_a(block) ;
	}


	inline stlsoft::basic_shim_string<stlsoft::ss_char_a_t>  c_str_data(
			const DataBlock& block) {
		return c_str_data_a(&block) ;
	}


	inline stlsoft::basic_shim_string<stlsoft::ss_char_a_t>  c_str_data_a(
			const DataBlock& block) {
		return c_str_data_a(&block) ;
	}


	inline stlsoft::ss_size_t c_str_len(const DataBlock& block) {
		return c_str_len_a(&block) ;
	}

	inline stlsoft::ss_size_t c_str_len_a(const DataBlock& block) {
		return c_str_len_a(&block) ;
	}


	inline stlsoft::basic_shim_string<stlsoft::ss_char_a_t> c_str_ptr_a(
			const DataBlock& block) {
		return c_str_data_a(&block) ;
	}

	inline stlsoft::basic_shim_string<stlsoft::ss_char_a_t> c_str_ptr(
			const DataBlock& block) {
		return c_str_data_a(&block) ;
	}

	inline stlsoft::basic_shim_string<stlsoft::ss_char_a_t> c_str_ptr_null_a(
			const DataBlock& block) {
		return c_str_data_a(&block) ;
	}


	inline stlsoft::basic_shim_string<stlsoft::ss_char_a_t> c_str_ptr_null(
			const DataBlock& block) {
		return c_str_data_a(&block) ;
	}
  }

}

namespace stlsoft {
	using ::WebGame::Message::c_str_data_a ;
	using ::WebGame::Message::c_str_len_a ;
	using ::WebGame::Message::c_str_ptr_a ;
	using ::WebGame::Message::c_str_ptr ;
	using ::WebGame::Message::c_str_ptr_null_a ;
	using ::WebGame::Message::c_str_ptr_null ;
	using ::WebGame::Message::c_str_data ;
}


#endif
