function(copy_resources TARGET_NAME)
	# remove the existing assets folder from the build directory (ensures removes are also replicated)
	add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E rm -rf $<TARGET_FILE_DIR:${TARGET_NAME}>/assets
	)

	# copy the assets folder in the target build directory
	add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${SURVIVANT_ASSETS_DIR} $<TARGET_FILE_DIR:${TARGET_NAME}>/assets
	)

	# remove unwanted files
	add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E rm -f $<TARGET_FILE_DIR:${TARGET_NAME}>/.gitkeep $<TARGET_FILE_DIR:${TARGET_NAME}>/CMakeLists.txt
	)
	
	message(STATUS "Resources added to target ${TARGET_NAME}")
endfunction()