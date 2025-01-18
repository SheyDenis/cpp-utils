# Sets compiler warning flags for the specified target.
#
# Parameters:
#   TARGET - The target to which the compiler warning flags will be applied.
#
# Usage:
#   SET_COMPILER_WARNING_FLAGS(<target>)
#
# Example:
#   SET_COMPILER_WARNING_FLAGS(my_target)
FUNCTION(SET_COMPILER_WARNING_FLAGS TARGET)
    TARGET_COMPILE_OPTIONS(${TARGET} PRIVATE
                           -Werror=all
                           -Werror=cast-align=strict
                           -Werror=conversion
                           -Werror=duplicated-branches
                           -Werror=duplicated-cond
                           -Werror=effc++
                           -Werror=extra
                           -Werror=float-equal
                           -Werror=format-security
                           -Werror=format=2
                           -Werror=logical-op
                           -Werror=missing-include-dirs
                           -Werror=narrowing
                           -Werror=non-virtual-dtor
                           -Werror=nonnull
                           -Werror=null-dereference
                           -Werror=old-style-cast
                           -Werror=overloaded-virtual
                           -Werror=pedantic
                           -Werror=reorder
                           -Werror=shadow
                           -Werror=sign-conversion
                           -Werror=unused
                           -Werror=unused-const-variable
                           -Werror=unused-function
                           -Werror=unused-local-typedefs
                           -Werror=unused-parameter
                           -Werror=unused-result
                           -Werror=unused-variable
                           -Werror=useless-cast
                           -Werror=write-strings

                           $<$<BOOL:${IS_DEV}>:-Wno-unused-const-variable>
                           $<$<BOOL:${IS_DEV}>:-Wno-unused-parameter>
                           $<$<BOOL:${IS_DEV}>:-Wno-unused>
    )
ENDFUNCTION(SET_COMPILER_WARNING_FLAGS)

# Sets sanitizer flags for the specified target.
#
# Parameters:
#   TARGET - The target to which the sanitizer flags will be applied.
#
# Usage:
#   SET_SANITIZER_FLAGS(<target>)
#
# Example:
#   SET_SANITIZER_FLAGS(my_target)
FUNCTION(SET_SANITIZER_FLAGS TARGET)
    MESSAGE(WARNING "SET_SANITIZER_FLAGS is not implemented yet.")
ENDFUNCTION(SET_SANITIZER_FLAGS)
