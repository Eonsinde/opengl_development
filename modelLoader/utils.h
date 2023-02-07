#ifndef __HOUND_UTILS_H__
#define __HOUND_UTILS_H__

#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <stb_image/stb_image.h>


namespace Hound {
	class IPrintable {
		friend std::ostream& operator<<(std::ostream&, const IPrintable&);
	public:
		IPrintable() = default;
		virtual ~IPrintable() = default;

	protected:
		virtual void print(std::ostream&) const = 0;
	};

	

	struct RectCollider : public IPrintable {
		int x0, y0, x1, y1;

		void print(std::ostream& os) const override {
			os << "x0: " << x0 << " y0: " << y0 << " x1: " << x1 << " y1: " << y1;
		}
	};

	bool hasIntersection(RectCollider, RectCollider);

	// Defined type to hold tokens
	typedef std::vector<const char*> TokenVector;

	// sentence and delimiter
	TokenVector tokenize(std::string, std::string=" ");

	// sentence,(reference)where to store tokens and delimiter
	void tokenize(std::string, TokenVector&, std::string=" ");


	// sentence, (ptr)where to store tokens and delimiter
	void tokenize(std::string, TokenVector*, std::string=" ");
}


#endif