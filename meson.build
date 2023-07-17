# This file is a part of marzer/tagged_ptr and is subject to the the terms of the MIT license.
# Copyright (c) Mark Gillard <mark.gillard@outlook.com.au>
# See https://github.com/marzer/tagged_ptr/blob/master/LICENSE for the full license text.
# SPDX-License-Identifier: MIT

project(
	'tagged_ptr',
	'cpp',
	version : '0.3.0',
	meson_version : '>=0.60.0',
	license : 'MIT',
	default_options : [ 'cpp_std=c++17' ]
)

subdir('include')

tagged_ptr_dep = declare_dependency(
    include_directories: include_dir
)

if not meson.is_subproject() and get_option('build_tests')
	subdir('tests')
endif


