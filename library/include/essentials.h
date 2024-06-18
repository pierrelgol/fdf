/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:32:59 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:32:59 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef DEBUG
#define DEBUG 0
#endif

/**********/
/* STRING */
/**********/

uint64_t string_length(const char *const source);
uint64_t string_copy(char *const dest, const char *const source, const uint64_t dsize);
uint64_t string_concat(char *const dest, const char *const source, const uint64_t dsize);
uint64_t string_span(const char *const source, const char *const delimiters);
uint64_t string_count(const char *const source, const char *const delimiters);
uint64_t string_wcount(const char *const source, const char *const delimiters);
uint64_t string_cspan(const char *const source, const char *const delimiters);
int64_t  string_index_of(const char *source, const int32_t ch);
int64_t  string_compare(const char *const source1, const char *const source2);
int64_t string_ncompare(const char *const source1, const char *const source2, const uint64_t n);
char *string_clone(const char *const source);
char *string_nclone(const char *const source, const uint64_t n);
char *string_join(const char *const source1, const char *const source2);
char *string_search(const char *const haystack, const char *const needle, const uint64_t n);
char   **string_tokenize(const char *const source, const int32_t ch);
uint64_t split_length(char **split);
char   **split_destroy(char **split);
char   **split_create(const uint64_t size);
uint64_t split_size(char **split);

/**********/
/* memory */
/**********/

int64_t memory_compare(const void *const source1, const void *const source2, const uint64_t n);
void *memory_search(const void *const source, const int32_t byte, const uint64_t ssize);
void *memory_ccopy(void *const dest, const int32_t byte, const void *const source, const uint64_t dsize);
void *memory_copy(void *const dest, const void *const source, const uint64_t bytes);
void *memory_move(void *const dest, const void *const src, const uint64_t bytes);
void *memory_fill(void *const dest, const int32_t byte, const uint64_t dsize);
void *memory_zero(void *const dest, const uint64_t dsize);
void *memory_alloc(const uint64_t size);
void *memory_dupe(const void *const source, const uint64_t size);
void *memory_dupz(const void *const source);
void  memory_dealloc(void *const ptr);

/*********/
/* ascii */
/*********/

bool is_alpha(const int32_t ch);
bool is_alnum(const int32_t ch);
bool is_space(const int32_t ch);
bool is_ctrl(const int32_t ch);
bool is_ascii(const int32_t ch);
bool is_print(const int32_t ch);
bool is_newline(const int32_t ch);
bool is_punct(const int32_t ch);
bool is_digit(const int32_t ch);
bool is_lower(const int32_t ch);
bool is_upper(const int32_t ch);
bool is_hex(const int32_t ch);
bool is_graph(const int32_t ch);

typedef int(t_print_fmt)(va_list arg, int fd);

typedef struct s_printer
{
	t_print_fmt *fmt;

} t_printer;

int32_t put_unumber_base(uint64_t num, const char *base, int32_t radix, int fd);
int32_t put_inumber_base(int64_t num, const char *base, int32_t radix, int fd);
int     put_char(va_list arg, int fd);
int     put_string(va_list arg, int fd);
int     put_int32(va_list arg, int fd);
int     put_ilong64(va_list arg, int fd);
int     put_ulong64(va_list arg, int fd);
int     put_uint32(va_list arg, int fd);
int     put_lowhex32(va_list arg, int fd);
int     put_upehex32(va_list arg, int fd);
int     put_ptr(va_list arg, int fd);
int     put_err(va_list arg, int fd);
t_printer print_fmt_parser(const char *fmt);
int32_t   arg_len(const char *fmt);
int32_t   print(const char *fmt, ...);
int32_t   fprint(int32_t fd, const char *fmt, ...);

#endif
