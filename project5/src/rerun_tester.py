#!/usr/bin/env python3
"""Python Hash Table tester

A "test driver" for the python hash table.
I've learned since P3. Hopefully some bugs will be found.

Change the value of ALWAYS_INSERT to match if necessary.
"""
from wgraph import DistanceGraph
# Only works with int test files ...
TEST_FILENAME = './tmp_test.int.in.txt'
graph = None
with open(TEST_FILENAME, 'r') as test_file:
    for i, line in enumerate(test_file):
        i += 1
        line = line.strip().split(" ")
        error_msg_start = "On line %d: " % i

        # Modifications
        if line[0] == "new":
            graph = DistanceGraph(50)

        elif line[0] == "new:":
            graph = DistanceGraph(int(line[1]))

        elif line[0] == "insert":
            try:
                graph.insert(int(line[1]), int(line[2]), float(line[3]))
            except ValueError:
                assert(False), error_msg_start + "Expected insert to be OK, but got overflow error"

        elif line[0] == "insert!":
            try:
                graph.insert(int(line[1]), int(line[2]), float(line[3]))
                assert(False), error_msg_start + "Expected insert to throw an overflow but got OK"
            except ValueError:
                pass

        elif line[0] == "distance":
            expected_dist_result = float(line[3])
            actual_dist_result = graph.distance(int(line[1]), int(line[2]))

            nice_error_msg = ("Expected distance from %d to %d to "
                              "be %.2f but it was actually %.2f.") % (
                                  int(line[1]), int(line[2]),
                                  expected_dist_result, actual_dist_result
                              )
            assert(expected_dist_result == actual_dist_result), error_msg_start + nice_error_msg

        elif line[0] == "~connected":
            expected_dist_result = float('inf')
            actual_dist_result = graph.distance(int(line[1]), int(line[2]))

            nice_error_msg = ("Expected distance from %d to %d to "
                              "be %.2f but it was actually %.2f.") % (
                                  int(line[1]), int(line[2]),
                                  expected_dist_result, actual_dist_result
                              )
            assert(expected_dist_result == actual_dist_result), error_msg_start + nice_error_msg

        elif line[0] == "adjacent":
            expected_edge_result = float(line[3])
            try:
                actual_edge_result = graph.adjacent(int(line[1]), int(line[2]))

                nice_error_msg = ("Expected edge from %d to %d to "
                                  "be %.2f but it was actually %.2f.") % (
                                      int(line[1]), int(line[2]),
                                      expected_dist_result, actual_dist_result
                                  )
                assert(expected_edge_result == actual_edge_result), error_msg_start + nice_error_msg
            except ValueError:
                assert(False), error_msg_start + "Expected edge check to be OK, but got value error"

        elif line[0] == "~adjacent":
            expected_edge_result = float('inf')
            try:
                actual_edge_result = graph.adjacent(int(line[1]), int(line[2]))

                nice_error_msg = ("Expected edge from %d to %d to "
                                  "be %.2f but it was actually %.2f.") % (
                                      int(line[1]), int(line[2]),
                                      expected_dist_result, actual_dist_result
                                  )
                assert(expected_edge_result == actual_edge_result), error_msg_start + nice_error_msg
            except ValueError:
                assert(False), error_msg_start + "Expected edge check to be OK, but got value error"

        elif line[0] == "adjacent!":
            nice_error_msg = ("Expected error in checking edge from %d to %d "
                              " but it was actually passed.") % (
                                  int(line[1]), int(line[2]),
                              )
            try:
                graph.adjacent(int(line[1]), int(line[2]))
                assert(False), error_msg_start + nice_error_msg
            except ValueError:
                pass

        elif line[0] == "degree":
            expected_deg_result = int(line[2])
            try:
                actual_deg_result = graph.degree(int(line[1]))
                nice_error_msg = "Expected degree of %d but it was actually %d" % (
                    expected_deg_result, actual_deg_result
                )
                assert(expected_deg_result == actual_deg_result), error_msg_start + nice_error_msg
            except ValueError:
                assert(False), error_msg_start + (
                    "Expected degree of %d, but got an error" % expected_deg_result
                )

        elif line[0] == "edge_count":
            expected_result = int(line[1])
            actual_result = graph.edge_count()
            nice_error_msg = "Expected number of edges to be %d but it was actually %d" % (
                expected_result, actual_result
            )
            assert(expected_result == actual_result), error_msg_start + nice_error_msg

        # Verifiers
        elif line[0] in ("//break", "cout"):
            print(str(graph))
            input("Press any key to continue ...")

print("Everything is AWESOME!")
