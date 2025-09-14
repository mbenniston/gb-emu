cmake_minimum_required(VERSION 3.21)

install(TARGETS gbemu-native
        RUNTIME DESTINATION bin)

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "GBEmu")
set(CPACK_PACKAGE_VENDOR "mbenniston")
set(CPACK_PACKAGE_VERSION "0.0.0")
set(CPACK_PACKAGE_CONTACT "")

set(CPACK_PACKAGING_INSTALL_PREFIX ".")

include(CPack)