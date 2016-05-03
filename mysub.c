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

		if (QCOUNT(1, myarray1) == 4 || QCOUNT(1, myarray3) == 4) 
		{
			return 1;
		} else {
			return 0;
		}

	} else {

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
		}
	} else {
		index_array[pointer++] = i;
		majority_count += 1;
	}

	mtr.majority_count = majority_count;
	mtr.pointer = pointer;

	return mtr;
}

int mysub( int n ) {
	int myarray[4];
	int qcount_results[2500];
	int two_index[2500];
	int four_index[2500];
	int return_index = 0, qcount_result, issame_result, test_ind, two_pointer = 0, four_pointer = 0, two_majority = 0, four_majority = 0;
	int i;
	int results_pointer = 0;
	int leftover = n % 4;
	printf("leftover: %d\n", leftover);
	for (i = 1; i < n - leftover; i+= 4)
	{
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

	if (two_majority > 0 && four_majority > 0) {

		if (issame(four_indexes, two_indexes, 2) == 1) {
			return_index = four_index_start;
		} else {
			//get difference
			//return index from greater majority

			int difference = (4 * four_majority) - (2 * two_majority);
			
			printf("difference %d\n", difference);

			if (difference == 2 && leftover == 2) {

				int remain_1 = n - leftover + 1;
				int remain_2 = n - leftover + 2;

				myarray[0] = remain_1;
				myarray[1] = remain_2;
				myarray[2] = four_indexes[0];
				myarray[3] = four_indexes[1];

				if (QCOUNT(1, myarray) == 0) {
					return_index = 0;
				} else {
					return_index = four_index_start;
				}

			} else if (difference == -2 && leftover == 2) {

				int remain_1 = n - leftover + 1;
				int remain_2 = n - leftover + 2;

				myarray[0] = remain_1;
				myarray[1] = remain_2;
				myarray[2] = four_indexes[0];
				myarray[3] = four_indexes[1];

				if (QCOUNT(1, myarray) == 4) {
					return_index = 0;
				} else {
					four_indexes[0] = remain_1;
					if (QCOUNT(1, four_indexes) == 2) {
						return_index = remain_1;
					} else {
						return_index = remain_2;
					}
				}

			} else if (difference == 2 && leftover == 3) {

				int remain_1 = n - leftover + 1;
				int remain_2 = n - leftover + 2;
				int remain_3 = n - leftover + 3;

				myarray[0] = remain_1;
				int qcount_1 = QCOUNT(1, myarray);
				myarray[0] = remain_2;
				int qcount_2 = QCOUNT(1, myarray);
				myarray[0] = remain_3;
				int qcount_3 = QCOUNT(1, myarray);

				if (qcount_1 == qcount_2 && qcount_2 == qcount_3) {
					return_index = n;
				} else {
					return_index = four_index_start;	
				}

			} else if (difference == -2 && leftover == 3) {

				int remain_1 = n - leftover + 1;
				int remain_2 = n - leftover + 2;
				int remain_3 = n - leftover + 3;

				myarray[0] = remain_1;
				int qcount_1 = QCOUNT(1, myarray);
				myarray[0] = remain_2;
				int qcount_2 = QCOUNT(1, myarray);
				myarray[0] = remain_3;
				int qcount_3 = QCOUNT(1, myarray);

				if (qcount_1 == qcount_2 && qcount_2 == qcount_3) {
					return_index = n;
				} else {
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
				}

			} else if (difference > 0) {
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

				if (leftover == 1) {

					return_index = n;

				} else if (leftover == 2) {
					// see if same
					// if same, refturn 1
					// else return 0

					int remain_1 = n - leftover + 1;
					int remain_2 = n - leftover + 2;

					myarray[0] = remain_1;
					int qcount_1 = QCOUNT(1, myarray);
					myarray[0] = remain_2;
					int qcount_2 = QCOUNT(1, myarray);

					if (qcount_1 == qcount_2) {
						return_index = n;
					} else {
						return_index = 0;
					}

				} else if (leftover == 3) {

					int remain_1 = n - leftover + 1;
					int remain_2 = n - leftover + 2;
					int remain_3 = n - leftover + 3;

					myarray[0] = remain_1;
					int qcount_1 = QCOUNT(1, myarray);
					myarray[0] = remain_2;
					int qcount_2 = QCOUNT(1, myarray);
					myarray[0] = remain_3;
					int qcount_3 = QCOUNT(1, myarray);

					if (qcount_1 == qcount_2) {
						return_index = remain_1;
					} else if (qcount_1 == qcount_3) {
						return_index = remain_1;
					} else {
						return_index = remain_2;
					}


				} else {
					return_index = 0;	
				}
			}
		}
	} else if (two_majority > 0 && four_majority == 0) {
		// Still need to account for remainder if input not multiple of 4

		if (two_majority > 1 || leftover <= 1) {
		
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

			if (leftover == 2) {
				int remain_1 = n - leftover + 1;
				int remain_2 = n - leftover + 2;

				myarray[0] = remain_1;
				int qcount_1 = QCOUNT(1, myarray);
				myarray[0] = remain_2;
				int qcount_2 = QCOUNT(1, myarray);

				if (qcount_1 == qcount_2) {
					//check if same majority as two majority
					int myarray1[4], myarray2[4];
					myarray1[0] = remain_1;
					myarray1[1] = remain_2;
					myarray1[2] = two_indexes[0];
					myarray1[3] = two_indexes[1];

					myarray2[0] = remain_1;
					myarray2[1] = remain_2;
					myarray2[2] = two_indexes[2];
					myarray2[3] = two_indexes[3];

					if (QCOUNT(1, myarray1) == 4 || QCOUNT(1, myarray2) == 4) {
						return_index = n;
					} else {
						return_index = 0;
					}
				} else {
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
				}

			} else if (leftover == 3) {
				int remain_1 = n - leftover + 1;
				int remain_2 = n - leftover + 2;
				int remain_3 = n - leftover + 3;

				myarray[0] = remain_1;
				int qcount_1 = QCOUNT(1, myarray);
				myarray[0] = remain_2;
				int qcount_2 = QCOUNT(1, myarray);
				myarray[0] = remain_3;
				int qcount_3 = QCOUNT(1, myarray);

				if (qcount_1 == qcount_2 && qcount_2 == qcount_3) {
					return_index = n;
				} else {
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
				}
			}

		}
	} else if (two_majority == 0 && four_majority > 0) {
		return_index = four_index[four_pointer - 1];
	} else if (two_majority == 0 && four_majority == 0) {
		// Still need to account for remainder if input not multiple of 4
		if (leftover == 1) {
			return_index = n;
		} else if (leftover == 2) {
			// see if same
			// if same, refturn 1
			// else return 0

			int remain_1 = n - leftover + 1;
			int remain_2 = n - leftover + 2;

			myarray[0] = remain_1;
			int qcount_1 = QCOUNT(1, myarray);
			myarray[0] = remain_2;
			int qcount_2 = QCOUNT(1, myarray);

			if (qcount_1 == qcount_2) {
				return_index = n;
			} else {
				return_index = 0;
			}
		} else if (leftover == 3) {


			int remain_1 = n - leftover + 1;
			int remain_2 = n - leftover + 2;
			int remain_3 = n - leftover + 3;

			myarray[0] = remain_1;
			int qcount_1 = QCOUNT(1, myarray);
			myarray[0] = remain_2;
			int qcount_2 = QCOUNT(1, myarray);
			myarray[0] = remain_3;
			int qcount_3 = QCOUNT(1, myarray);

			if (qcount_1 == qcount_2) {
				return_index = remain_1;
			} else if (qcount_1 == qcount_3) {
				return_index = remain_1;
			} else {
				return_index = remain_2;
			}


		} else {
			return_index = 0;	
		}
		
	}
	// printf("%d\n", return_index);
	return return_index;
}