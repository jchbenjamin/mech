class auctionItem
{
	private:
		std::string desc;
		int order;
	public:
		auctionItem(std::string d, int o) : desc(d), order(o);
		auctionItem(std::string d) : desc(d), order(0);
		std::string getDesc() { return desc };
		int getO() { return order; };
		void setO(int o) { order = o; };
}

class itemCollection
{
	std::vector< auctionItem > items;
}


