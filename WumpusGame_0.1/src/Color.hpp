namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
		FG_YELLOW   = 33,
		FG_MAGENTA  = 35,
		FG_CYAN     = 36,
        FG_DEFAULT  = 39,
    };
    
	inline std::ostream& operator<<(std::ostream& os, Code code)
	{
		return os << "\033[" << static_cast<int>(code) << "m";
	} 
}