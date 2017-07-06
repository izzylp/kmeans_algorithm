#ifndef _KMEANS_POINT_HPP_
#define _KMEANS_POINT_HPP_

#include <cstdint>
#include <vector>
#include <string>

class kmeans_point
{
public:
	kmeans_point();
	kmeans_point(size_t);
	kmeans_point(std::initializer_list<double>);
	void push_back(double);
	void push_back_label(std::string);
	void set_belongs_to(size_t);
	size_t n_dimensions() const;
	size_t belongs_to(size_t) const;
	bool operator==(const kmeans_point&) const;
	bool operator!=(const kmeans_point&) const;
	bool operator<(const kmeans_point&) const;
	kmeans_point operator+(const kmeans_point&);
	kmeans_point operator/(double);
	double euclidean_distance(const kmeans_point&);
	std::string to_string() const;

private:
	size_t n_dimensions_;
	size_t belongs_to_;
	std::vector<double> p_;
	std::vector<std::string> labels_;
};

kmeans_point::kmeans_point()
{
}

kmeans_point::kmeans_point(size_t n_dimensions_)
{
	this->n_dimensions_ = n_dimensions_;
	belongs_to_ = 0;
}

kmeans_point::kmeans_point(std::initializer_list<double> init)
{
	n_dimensions_ = init.size();
	belongs_to_ = 0;
	for (const double& item : init) {
		p_.push_back(item);
	}
}

void kmeans_point::push_back(double item_)
{
	p_.push_back(item_);
}

void kmeans_point::push_back_label(std::string item_)
{
	labels_.push_back(item_);
}

void kmeans_point::set_belongs_to(size_t belongs_to_)
{
	this->belongs_to_ = belongs_to_ + 1;
}

size_t kmeans_point::n_dimensions() const
{
	return n_dimensions_;
}

size_t kmeans_point::belongs_to(size_t belongs_to_) const
{
	return (this->belongs_to_ == belongs_to_ + 1);
}

bool kmeans_point::operator==(const kmeans_point& that) const
{
	bool ret = true;
	auto it1 = this->p_.begin();
	auto it2 = that.p_.begin();

	for (; it1 != this->p_.end(); ++it1, ++it2) {
		if (*it1 != *it2) {
			ret = false;
		}
		break;
	}
	
	return ret;
}

bool kmeans_point::operator!=(const kmeans_point& that) const
{
	return !(*this == that);
}

bool kmeans_point::operator<(const kmeans_point& that) const
{
	return (this->belongs_to_ < that.belongs_to_);
}

kmeans_point kmeans_point::operator+(const kmeans_point& that)
{
	kmeans_point ret(this->n_dimensions_);
	auto it1 = this->p_.begin();
	auto it2 = that.p_.begin();

	for (; it1 != this->p_.end(); ++it1, ++it2) {
		ret.push_back(*it1 + *it2);
	}

	return ret;
}

kmeans_point kmeans_point::operator/(double that)
{
	kmeans_point ret(this->n_dimensions_);
	auto it1 = this->p_.begin();

	for (; it1 != this->p_.end(); ++it1) {
		ret.push_back(*it1 / that);
	}

	return ret;
}

double kmeans_point::euclidean_distance(const kmeans_point& that)
{
	double ret = 0.0;
	auto it1 = this->p_.begin();
	auto it2 = that.p_.begin();

	for (; it1 != this->p_.end(); ++it1, ++it2) {
		ret += pow(*it1 - *it2, 2);
	}

	ret = sqrt(ret);
	return ret;
}

std::string kmeans_point::to_string() const
{
	std::string ret = "(";

	for (size_t i = 0; i < p_.size(); ++i) {
		if (i + 1 == p_.size()) {
			ret.append(std::to_string(p_[i]));
		} else {
			ret.append(std::to_string(p_[i]));
			ret.append(" ");
		}
	}
	ret.append(") ");

	for (size_t i = 0; i < labels_.size(); ++i) {
		ret.append(labels_[i]);
		ret.append(" ");
	}

	if (belongs_to_ != 0) {
		ret.append(" in centroid ");
		ret.append(std::to_string(belongs_to_));
	}

	return ret;
}

#endif
