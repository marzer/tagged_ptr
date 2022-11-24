# This file is a part of marzer/tagged_ptr and is subject to the the terms of the MIT license.
# Copyright (c) Mark Gillard <mark.gillard@outlook.com.au>
# See https://github.com/marzer/tagged_ptr/blob/master/LICENSE for the full license text.
# SPDX-License-Identifier: MIT

test_exe = executable(
	'test_exe',
	files('main.cpp'),
	dependencies:
	[
		tagged_ptr_dep,
		subproject('catch2', default_options: [ 'warning_level=0', 'werror=false' ]).get_variable('catch2_with_main_dep')
	],
	override_options: [ 'warning_level=3', 'werror=true' ],
	install: false
)

test('test', test_exe)
