# CMake project for FOVE C++ Examples
cmake_minimum_required(VERSION 2.6)
project(FoveCppExamples)

# Find the Fove SDK
if("${CppExampleBuildInTree}")

	# This allows building within the the FOVE SDK source checkout (for FOVE developers)
	message(STATUS "Building FOVE CPP Examples in tree")
	link_libraries(FoveClientStatic)

else()

	# Setup a FOVE_SDK_PATH variable to allow using a FOVE SDK from a custom location
	# This older variable is no longer used since probably it got cached to an old SDK name
	set(FOVE_SDK_PATH "" CACHE PATH "Directory of extracted FOVE SDK")
	unset(FOVE_SDK_FOLDER CACHE)

	# Find the sdk path (falling back to the built-in one if FOVE_SDK_PATH is not set)
	set(sdk_folder "${CMAKE_CURRENT_LIST_DIR}/FOVE SDK 0.14.0") # Path to builtin sdk folder
	if(NOT "${FOVE_SDK_PATH}" STREQUAL "")
		# Custom error message that suggests using the built-in release if you are pointing to a bad folder
		if(NOT EXISTS "${FOVE_SDK_PATH}" AND EXISTS "${sdk_folder}")
			message(FATAL_ERROR "Unable to find FOVE SDK at ${sdk_folder}\nPlease set FOVE_SDK_PATH to the location of the FOVE SDK.\nSuggested path: ${sdk_folder}")
		endif()
		set(sdk_folder "${FOVE_SDK_PATH}")
	endif()

	# Ensure the sdk folder is valid
	if(NOT EXISTS "${sdk_folder}")
		message(FATAL_ERROR "Unable to find FOVE SDK. Please set FOVE_SDK_PATH to the location of the FOVE SDK.\nNo folder exists at: ${sdk_folder}")
	endif()
	if(NOT EXISTS "${sdk_folder}/include/IFVRHeadset.h")
		message(FATAL_ERROR "Unable to find FOVE SDK headers. Please set FOVE_SDK_PATH to the location of the FOVE SDK.\nNo file exists at: ${sdk_folder}/include/IFVRHeadset.h")
	endif()
	message(STATUS "Using FOVE SDK at ${sdk_folder}")

	# Locate the client dynamic library
	set(FoveClient "${sdk_folder}/bin/FoveClient.dll")
	if(NOT EXISTS "${FoveClient}")
		message(FATAL_ERROR "Missing Fove library at ${FoveClient}")
	endif()

	# Setup build parameters
	set(CMAKE_CXX_STANDARD 11)
	add_definitions(-DUNICODE)
	include_directories("${sdk_folder}/include")
	link_libraries("${sdk_folder}/lib/FoveClient.lib")
endif()

# Determine the utility headers we have for the current platform
if(WIN32)
	set(NativeUtilFiles WIN32 NativeUtil.h WindowsUtil.h WindowsUtil.cpp)
else()
	set(NativeUtilFiles NativeUtil.h)
endif()

add_library(DataCapture STATIC
	DataCapture.cpp
	DataCapture.h
	Util.cpp
	Util.h
)

add_executable(FOVE_BUILD_DATA_EXAMPLE
	Main.cpp
)

target_link_libraries(FOVE_BUILD_DATA_EXAMPLE
	DataCapture)

list(APPEND alltargets DataCapture)

# Add a post-build command to each target to copy the FoveClient dynamic library to the executable location
# Otherwise the executable will not be able to find the dll, and will fail to launch
if(FoveClient)
	foreach(target ${alltargets})
		add_custom_command(TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${FoveClient}" $<TARGET_FILE_DIR:${target}>)
	endforeach()
endif()

# # Set default startup project to something other than cmake's ALL_BUILD target
# # This way anyone hitting build-and-run will run one of the targets instead of ALL_BUILD which isn't runable
if(MSVC AND NOT "${CppExampleBuildInTree}" AND alltargets)
	list(GET alltargets 0 FirstTarget)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${FirstTarget})
endif()
