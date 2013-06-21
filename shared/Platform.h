/*
 * =====================================================================================
 *
 *       Filename:  Platform.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/5/31 10:00:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef WEBGAME_PLATFORM_H
#define WEBGAME_PLATFORM_H
#ifdef _WIN32
#define CONSTEXPR inline
#define NOEXCEPT
#else
#define CONSTEXPR constexpr
#define NOEXCEPT noexcept
#endif
#endif
