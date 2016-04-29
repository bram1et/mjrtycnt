int reference[2] = {-1, -1};
int ref_majority = 0;
int size = 0;

int issame(int array1[4], int array2[4], int is_4) {
	int myarray1[4] = {array1[0], array1[1], array2[0], array2[1]};
	int myarray2[4] = {array1[2], array1[3], array2[2], array2[3]};
	int myarray3[4] = {array1[0], array1[1], array2[2], array2[3]};
	int myarray4[4] = {array1[2], array1[3], array2[0], array2[1]};

	if (is_4 == 1)
	{
		if (QCOUNT(1, myarray1) == 4) {
			return 1;
		} else {
			return 0;
		}

	} else if (is_4 == 2) {

		if (QCOUNT(1, myarray1) == 4 || QCOUNT(1, myarray3) == 4) {
			return 1;
		} else {
			return 0;
		}

	} else if (is_4 == 0) {

		if (reference[0] != -1) {
			
			myarray1[2] = reference[0];
			myarray1[3] = reference[1];

			myarray2[2] = reference[0];
			myarray2[3] = reference[1];
			if (QCOUNT(1, myarray1) == 4 || QCOUNT(1, myarray2) == 4) {
				return 1;
			} else {
				return 0;
			}

		}

		if (QCOUNT(1, myarray1) == 4 || QCOUNT(1, myarray2) == 4 || QCOUNT(1, myarray3) == 4 || QCOUNT(1, myarray4) == 4) {
			return 1;
		} else {
			return 0;	
		}

	}
	
}

struct majority_test_return {
	int majority_count;
	int pointer;

};

struct majority_test_return majority_test(int pointer, int majority_count, int i, int index_array[2500], int myarray[4], int is_4) {
	struct majority_test_return mtr;
	int index = 0;
	
	if (pointer > 0) {
		index = index_array[pointer - 1];
		int test_array[4] = {index, index + 1, index + 2, index + 3};
		int issame_result = issame(myarray, test_array, is_4);
		if (issame_result == 1) {
			index_array[pointer++] = i;
			majority_count += 1;
		} else {
			pointer--;
			majority_count--;

			if (pointer <= 0 && is_4 == 0) {
				
				reference[0] = -1;
				reference[1] = -1;
			}
		}
	} else {

		index_array[pointer++] = i;
		majority_count += 1;

		if (is_4 == 0) {
			int test_array[4] = {index, index + 1, index + 2, index + 3};
			//get a test index
			int test_index;
			int qcount_result;
			if (reference[0] == -1) {
				if (index > 1) {
					test_index = 1;
				} else {
					test_index = size;
				}

				test_array[0] = test_index;
				qcount_result = QCOUNT(1, test_array);

				if (qcount_result == 0) {

					reference[0] = index;
					test_array[0] = index;
					test_array[1] = test_index;
					qcount_result = QCOUNT(1, test_array);

					if (qcount_result == 0) {
						reference[1] = index + 1;
					} else {
						reference[1] = index + 2;
					}

				} else if (qcount_result == 4) {

					reference[0] = index + 2;
					reference[1] = index + 3;

				} else if (qcount_result == 2) {

					test_array[0] = index;
					test_array[1] = test_index;
					qcount_result = QCOUNT(1, test_array);
					if (qcount_result == 0 || qcount_result == 4) {
						reference[0] = index + 2;
						reference[0] = index + 3;
					} else if (qcount_result == 2) {
						reference[0] = index;
						reference[0] = index + 1;
					}
				}
			}

		}
	}

	mtr.majority_count = majority_count;
	mtr.pointer = pointer;

	return mtr;
}

int mysub( int n ) {
	size = n;
	int myarray[4];
	int qcount_results[2500];
	int two_index[2500];
	int four_index[2500];
	int return_index = 0, qcount_result, issame_result, test_ind, two_pointer = 0, four_pointer = 0, two_majority = 0, four_majority = 0;
	int i;
	int results_pointer = 0;
	for (i = 1; i < n; i+= 4) {

		myarray[0] = i;
		myarray[1] = i + 1;
		myarray[2] = i + 2;
		myarray[3] = i + 3;

		qcount_result = QCOUNT(1, myarray);
		qcount_results[results_pointer++] = qcount_result;

		if (qcount_result == 2) {

			struct majority_test_return mtr = majority_test(two_pointer, two_majority, i, two_index, myarray, 0);
			two_pointer = mtr.pointer;
			two_majority = mtr.majority_count;
			
		} else if (qcount_result == 4) {

			struct majority_test_return mtr = majority_test(four_pointer, four_majority, i, four_index, myarray, 1);
			four_pointer = mtr.pointer;
			four_majority = mtr.majority_count;
		}
	}
	
	// printf("\n");
	// for (i = 0; i < results_pointer; ++i) {
	// 	printf("%d ",qcount_results[i]);
	// }
	// printf("\n");
	printf("two_majority:  %d\n", two_majority);
	printf("four_majority: %d\n", four_majority);
	// printf("\n");

	int two_index_start = two_index[two_pointer - 1];
	int two_indexes[4] = {two_index_start, two_index_start + 1, two_index_start + 2, two_index_start + 3};
	int four_index_start = four_index[four_pointer - 1];
	int four_indexes[4] = {four_index_start, four_index_start + 1, four_index_start + 2, four_index_start + 3};

	reference[0] = -1;
	reference[1] = -1;

	if (two_majority > 0 && four_majority > 0) {

		if (issame(four_indexes, two_indexes, 2) == 1) {
			return_index = four_index_start;
		} else {
			//get difference
			//return index from greater majority

			int difference = (4 * four_majority) - (2 * two_majority);
			if (difference > 0) {
				return_index = four_index_start;
			} else if (difference < 0) {
				// get majority index from 2_majority
				// get test index

				if (two_index_start == 1) {
					test_ind = n;
				} else {
					test_ind = 1;
				}

				two_indexes[0] = test_ind;
				qcount_result = QCOUNT(1, two_indexes);
				if (qcount_result == 0) {
					return_index = two_index_start;
				} else if (qcount_result == 4) {
					return_index = test_ind;
				} else if (qcount_result == 2) {
					two_indexes[0] = two_index_start;
					two_indexes[1] = test_ind;
					qcount_result = QCOUNT(1, two_indexes);
					if (qcount_result == 0) {
						return_index = two_index_start + 1;
					} else {
						return_index = two_index_start;
					}
				}
			} else {
				return_index = 0;
			}
		}

	} else if (two_majority > 0 && four_majority == 0) {
		// Still need to account for remainder if input not multiple of 4
		if (two_index_start == 1) {
			test_ind = n;
		} else {
			test_ind = 1;
		}

		two_indexes[0] = test_ind;
		qcount_result = QCOUNT(1, two_indexes);
		if (qcount_result == 0) {
			return_index = two_index_start;
		} else if (qcount_result == 4) {
			return_index = test_ind;
		} else if (qcount_result == 2) {
			two_indexes[0] = two_index_start;
			two_indexes[1] = test_ind;
			qcount_result = QCOUNT(1, two_indexes);
			if (qcount_result == 0) {
				return_index = two_index_start + 1;
			} else {
				return_index = two_index_start;
			}
		}
	} else if (two_majority == 0 && four_majority > 0) {
		return_index = four_index[four_pointer - 1];
	} else if (two_majority == 0 && four_majority == 0) {
		// Still need to account for remainder if input not multiple of 4
		return_index = 0;
	}
	// printf("%d\n", return_index);
	return return_index;
}