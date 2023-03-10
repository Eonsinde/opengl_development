#include "utils.h"


namespace Hound {
	std::ostream& operator<<(std::ostream& os, const IPrintable& rhsObj) {
		rhsObj.print(os);
		return os;
	}

	bool hasIntersection(RectCollider rectA, RectCollider rectB) {
		/*return (!(
			(rectB.x1 <= rectA.x0) ||
			(rectB.x0 >= rectA.x1) ||
			(rectB.y1 <= rectA.y0) ||
			(rectB.y0 >= rectA.y1)
		));*/
		bool resp = ((rectA.x0 < rectB.x1 && rectA.y0 < rectB.y1) && // bl of A < tr of B
			(rectA.x1 > rectB.x0 && rectA.y1 > rectB.y0));

		/*std::cout << "is intersecting: " << resp << std::endl;
		std::cout << "mSceneCollider: " << rectA << "\n";
		std::cout << "mMouseCollider: " << rectB << "\n";*/


		return  ((rectA.x0 < rectB.x1&& rectA.y0 < rectB.y1) && // bl of A < tr of B
				(rectA.x1 > rectB.x0 && rectA.y1 > rectB.y0));  // tl of A > bl of B
	}

	TokenVector tokenize(std::string s, std::string del)
	{
		TokenVector tokens;

		int start = 0;
		int end = s.find(del);

		while (end != -1) {
			tokens.push_back(s.substr(start, end - start).c_str());
			// update the start position since lower values have been served
			start = end + del.size(); // move forward by delimiter size
			end = s.find(del, start); // find delimiter again by setting start position
		}

		// if token is found again, see if it's not at the end of string, 
		// then, process data
		if (end != s.size() - 1)
			tokens.push_back(s.substr(start, end - start).c_str());

		//std::cout << s.substr(start, end - start);
		return tokens;
	}

	// sentence,(reference)where to store tokens and delimiter
	void tokenize(std::string s, TokenVector& pTokens, std::string del)
	{
		// this is a more optimized version 
		int start = 0;
		int end = s.find(del);

		while (end != -1) {
			pTokens.push_back(s.substr(start, end - start));
			// update the start position since lower values have been served
			start = end + del.size();
			end = s.find(del, start); // find delimiter again by setting start position
		}

		if (end != s.size() - 1)
			pTokens.push_back(s.substr(start, end - start).c_str());
	}

	// sentence, (ptr)where to store tokens and delimiter
	void tokenize(std::string s, TokenVector* pTokens, std::string del)
	{
		// this is a more optimized version 
		int start = 0;
		int end = s.find(del);

		while (end != -1) {
			pTokens->push_back(s.substr(start, end - start).c_str());
			// update the start position since lower values have been served
			start = end + del.size();
			end = s.find(del, start); // find delimiter again by setting start position
		}

		if (end != s.size() - 1)
			pTokens->push_back(s.substr(start, end - start).c_str());
	}
};