print_headline()
{
	local MSG="$1"
	printf '%b' "\033[34;1m${MSG}\033[0m\n"
}

print_info() {
	local MSG="$1"
	printf '%b' "\033[36m${MSG}\033[0m\n"
}

print_warning() {
	local MSG="$1"
	printf '%b' "\033[33;1m${MSG}\033[0m\n"
}

print_error() {
	local MSG="$1"
	printf '%b' "\033[31;1m${MSG}\033[0m\n"
}

echo_and_run() {
	local CMD="$1"
	echo "${CMD}"
	eval "${CMD}"
}

echo_var() {
	# echo "$1 = ${!1}" does not work in dash (Ubuntu's default sh)
	eval "echo \"$1 = \$$1\""
}
