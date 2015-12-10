#ifndef DATA_HPP_
#define DATA_HPP_

#include <SFML/System.hpp>
typedef sf::Vector2<double> vec2;

template<typename T>
inline bool operator<=(const sf::Vector2<T> & left, const sf::Vector2<T> & right) {
	return (left.x <= right.x) && (left.y <= right.y);
}
template<typename T>
inline bool operator>=(const sf::Vector2<T> & left, const sf::Vector2<T> & right) {
	return (left.x >= right.x) && (left.y >= right.y);
}

template<typename T>
inline bool operator<(const sf::Vector2<T> & left, const sf::Vector2<T> & right) {
	return (left.x < right.x) && (left.y < right.y);
}
template<typename T>
inline bool operator>(const sf::Vector2<T> & left, const sf::Vector2<T> & right) {
	return (left.x > right.x) && (left.y > right.y);
}

#include <vector>
using namespace std;



#endif
