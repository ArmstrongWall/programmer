cmake_minimum_required(VERSION 3.9)
project(leetcode)

find_package(Eigen3 REQUIRED)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -pthread")

include_directories (
        ${EIGEN3_INCLUDE_DIR}
        ${Sophus_INCLUDE_DIRS}
)

add_executable(leetcode src/main.cpp
        src/206_reverse_linked_list/reverse_linked_list.cpp
        src/92_reverse_linked_list_II/reverse_linked_list_II.cpp
        src/92_reverse_linked_list_II/reverse_linked_list_II.h
        src/160_get_intersection_node/getIntersectionNode.cpp
        src/160_get_intersection_node/getIntersectionNode.h
        src/142_detectCycle/detectCycle.cpp
        src/142_detectCycle/detectCycle.h
        src/86_partition_list/partition_list.cpp
        src/86_partition_list/partition_list.h
        src/138_copyRandomList/copyRandomList.cpp
        src/138_copyRandomList/copyRandomList.h
        src/21_mergeTwoLists/mergeTwoLists.cpp
        src/21_mergeTwoLists/mergeTwoLists.h
        src/23_mergeKLists/mergeKLists.cpp
        src/23_mergeKLists/mergeKLists.h
        src/224_basicCalculator/basic_calculator.cpp
        src/224_basicCalculator/basic_calculator.h
        src/225_make_stack_with_queue/stack_use_queue.cpp
        src/225_make_stack_with_queue/stack_use_queue.h
        src/215_Kth_largest_num/kth_largest_num.cpp
        src/215_Kth_largest_num/kth_largest_num.h
        src/295_find_median/find_median.cpp
        src/295_find_median/find_median.h
        src/155_min_stack/min_stack.cpp
        src/155_min_stack/min_stack.h
        src/232_make_queue_using_stacks/queue_use_stack.cpp
        src/232_make_queue_using_stacks/queue_use_stack.h
        src/455_assign_cookies/assign_cookies.cpp
        src/455_assign_cookies/assign_cookies.h
        src/376_wiggle_subsequence/wiggle_subsequence.cpp
        src/376_wiggle_subsequence/wiggle_subsequence.h
        src/78_subsets/subsets.cpp
        src/78_subsets/subsets.h
        src/402_remove_k_digits/remove_k_dig.cpp
        src/402_remove_k_digits/remove_k_dig.h
        src/55_jump_game/jump_game.cpp
        src/55_jump_game/jump_game.h
        src/162_find_peak/find_peak.cpp
        src/162_find_peak/find_peak.h
        src/45_jump_game_II/jump_game_II.cpp
        src/45_jump_game_II/jump_game_II.h
        src/452_burst_balloons/burst_balloons.cpp
        src/452_burst_balloons/burst_balloons.h
        src/315_count_smaller_numbers/count_smaller_numbers.cpp
        src/315_count_smaller_numbers/count_smaller_numbers.h
        src/90_subsets_II/subsets_II.cpp
        src/90_subsets_II/subsets_II.h
        src/113_path_sum_II/path_sum_II.cpp
        src/113_path_sum_II/path_sum_II.h src/40_combination_sum_II/combination_sum_II.cpp src/40_combination_sum_II/combination_sum_II.h src/22_generate_parentheses/generate_parentheses.cpp src/22_generate_parentheses/generate_parentheses.h src/51_N_queens/n_queens.cpp src/51_N_queens/n_queens.h)