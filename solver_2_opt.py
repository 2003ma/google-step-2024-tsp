#!/usr/bin/env python3

import sys
import math
from common import print_tour, read_input


def distance(city1, city2):
    return math.sqrt((city1[0] - city2[0]) ** 2 + (city1[1] - city2[1]) ** 2)


def solve(cities):
    N = len(cities)

    dist = [[0] * N for i in range(N)]
    for i in range(N):
        for j in range(i, N):
            dist[i][j] = dist[j][i] = distance(cities[i], cities[j])

    current_city = 0
    unvisited_cities = set(range(1, N))
    tour = [current_city]

    while unvisited_cities:
        next_city = min(unvisited_cities, key=lambda city: dist[current_city][city])
        unvisited_cities.remove(next_city)
        tour.append(next_city)
        current_city = next_city

    tour = two_opt(tour, dist)
    return tour


def two_opt(tour, dist, max_iterations=1000):
    N = len(tour)
    improvement = True
    iteration = 0

    while improvement and iteration < max_iterations:
        improvement = False
        for i in range(1, N - 1):
            for j in range(i + 1, N):
                if j - i == 1:
                    continue
                if (
                    dist[tour[i - 1]][tour[i]] + dist[tour[j]][tour[(j + 1) % N]]
                    > dist[tour[i - 1]][tour[j]] + dist[tour[i]][tour[(j + 1) % N]]
                ):
                    tour[i:j] = reversed(tour[i:j])
                    improvement = True
        iteration += 1

    return tour


if __name__ == "__main__":
    assert len(sys.argv) > 1
    tour = solve(read_input(sys.argv[1]))
    print_tour(tour)
