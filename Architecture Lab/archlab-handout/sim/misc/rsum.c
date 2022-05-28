long rsum_arr(long * ptr, int count) {
	if(count == 0)
		return 0;
	else {
		return (*ptr)+rsum_arr(ptr + 1, count - 1);
	}
}
