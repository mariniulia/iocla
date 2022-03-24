extern int qty;
void set_price(int price);
void print_price();
void print_quantity();

int main(void)
{
	qty = 42;
	set_price(21);
	print_price();
	print_quantity();
	/*
	 * TODO: Make it so you print:
	 *    price is 21
	 *    quantity is 42
	 * without directly calling a printing function from an existing
	 * library(do NOT use printf, fprintf, fwrite, ...).
	 */

	return 0;
}
