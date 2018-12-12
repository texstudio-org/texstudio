if(WIN32)
	get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
	get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
	find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
	add_custom_command(TARGET texstudio POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E
			env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
			--dir \"$<TARGET_FILE_DIR:texstudio>\"
			--plugindir \"$<TARGET_FILE_DIR:texstudio>/plugins\"
			--pdb
			--no-compiler-runtime
			\"$<TARGET_FILE:texstudio>\"
		COMMENT "Deploying Qt..."
	)
	foreach(_tf ${TRANSLATION_FILES})
		string(REPLACE ".ts" ".qm" _tfqb ${_tf})
		set(TRANSLATION_RESULTS ${TRANSLATION_RESULTS} ${_tfqb})
	endforeach()
	add_custom_command(TARGET texstudio POST_BUILD
		COMMAND cd ARGS /d "${CMAKE_SOURCE_DIR}"
		COMMAND "${CMAKE_COMMAND}" ARGS -E copy_if_different ${TRANSLATION_RESULTS} "$<TARGET_FILE_DIR:texstudio>/translations"
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	)
	function(texstudio_copy_all_files source_dir target_dir)
		file(GLOB TEMP_FILES ${source_dir}/*.*)
		add_custom_command(TARGET texstudio POST_BUILD
			COMMAND "${CMAKE_COMMAND}" ARGS -E make_directory "${target_dir}"
			COMMAND "${CMAKE_COMMAND}" ARGS -E copy_if_different ${TEMP_FILES} "${target_dir}"
		)
	endfunction()
	texstudio_copy_all_files("${CMAKE_SOURCE_DIR}/utilities/TexTablet" "$<TARGET_FILE_DIR:texstudio>/TexTablet")
	texstudio_copy_all_files("${CMAKE_SOURCE_DIR}/utilities/dictionaries" "$<TARGET_FILE_DIR:texstudio>/dictionaries")
	texstudio_copy_all_files("${CMAKE_SOURCE_DIR}/utilities/manual" "$<TARGET_FILE_DIR:texstudio>/help")
	texstudio_copy_all_files("${CMAKE_SOURCE_DIR}/templates" "$<TARGET_FILE_DIR:texstudio>/templates")
	if(Poppler_FOUND)
		get_filename_component(POPPLER_LIB_DIR ${Poppler_Qt5_LIBRARY} DIRECTORY)
		get_filename_component(POPPLER_LIB_NAME ${Poppler_Qt5_LIBRARY} NAME)
		string(REPLACE ".lib" ".dll" POPPLER_LIB_NAME ${POPPLER_LIB_NAME})
		find_file(Poppler_Qt5_DLL ${POPPLER_LIB_NAME} PATHS ${POPPLER_LIB_DIR}/.. ${POPPLER_LIB_DIR}/../bin PATH_SUFFIXES bin Debug Release x86 x64)
		add_custom_command(TARGET texstudio POST_BUILD
			COMMAND "${CMAKE_COMMAND}" ARGS -E copy_if_different ${Poppler_Qt5_DLL} "$<TARGET_FILE_DIR:texstudio>"
		)
	endif()
	install(TARGETS texstudio RUNTIME DESTINATION .)
	install(DIRECTORY "$<TARGET_FILE_DIR:texstudio>/" DESTINATION .)
endif(WIN32)