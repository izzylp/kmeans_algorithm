#ifndef _KMEANS_HPP_
#define _KMEANS_HPP_

#include "kmeans_point.hpp"

#include <vector>

std::vector<kmeans_point> generate_centroids(size_t k_, std::vector<kmeans_point>& points_)
{
	std::vector<kmeans_point> ret;

	for (size_t i = 0; i < k_; ++i) {
		ret.push_back(points_[0]);
	}

	return ret;
}

std::vector<kmeans_point> kmeans_solve(size_t k_, std::vector<kmeans_point>& points_)
{
	std::vector<kmeans_point> centroids_ = generate_centroids(k_, points_);
	std::vector<kmeans_point> prev_points_ = points_;
	std::vector<kmeans_point> prev_centroids_ = centroids_;

	for (;;) {
		/* Euclidean distances */
		for (size_t i = 0; i < points_.size(); ++i) {
			double min = points_[i].euclidean_distance(centroids_[0]);
			size_t i_min = 0;
			for (size_t j = 1; j < centroids_.size(); ++j) {
				double d = points_[i].euclidean_distance(centroids_[j]);
				if (min > d) {
					min = d;
					i_min = j;
				}
			}
			points_[i].set_belongs_to(i_min);
		}

		/* Recalculate centroids */
		for (size_t j = 0; j < centroids_.size(); ++j) {
			kmeans_point new_centroid;
			size_t count = 0;
			for (size_t i = 0; i < points_.size(); ++i) {
				if (points_[i].belongs_to(j)) {
					if (count == 0) {
						new_centroid = points_[i];
					} else {
						new_centroid = new_centroid + points_[i];
					}
					++count;
				}
			}
			if (count == 0) {
				new_centroid = centroids_[j];
			} else {
				new_centroid = new_centroid / count;
				centroids_[j] = new_centroid;
			}
		}

		if (prev_points_ == points_ && prev_centroids_ == centroids_) {
			break;
		}

		prev_points_ = points_;
		prev_centroids_ = centroids_;
	}

	return centroids_;
}

#endif
