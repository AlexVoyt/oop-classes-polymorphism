#include <iostream>
#include <vector>

enum PizzaSize
{
    SMALL = 25,
    MEDIUM = 30,
    LARGE = 35,
    VERY_LARGE = 40
};

class Pizza
{
    unsigned int saltiness = 0;
    unsigned int cheeseness = 0; // wat?

    protected:
    PizzaSize size;

    public:

#if 0
    void Set_Size(PizzaSize _size)
    {
        size = _size;
    }
#endif
    unsigned int Get_Saltiness()
    {
        return saltiness;
    }

    unsigned int Get_Cheeseness()
    {
        return cheeseness;
    }

    unsigned int Get_Size()
    {
        // TODO : to enum
        return size;
    }

    void Add_Salt(unsigned int value)
    {
        saltiness += value;
    }

    void Add_Cheese(unsigned int value)
    {
        cheeseness += value;
    }

    Pizza(PizzaSize _size, unsigned int _cheeseness, unsigned int _saltiness)
    {
        size = _size;
        Add_Cheese(_cheeseness);
        Add_Salt(_saltiness);
    }

    virtual void Print_Description()       = 0;
    virtual unsigned int Cost_For_Type()   = 0;
    virtual unsigned int Cost_Per_Salt()   = 0;
    virtual unsigned int Cost_Per_Cheese() = 0;

    //TODO : should be inlined, I guess?
    unsigned int Determine_Cost()
    {
        unsigned int cost_for_salt = saltiness*Cost_Per_Salt();
        unsigned int cost_for_cheese = cheeseness*Cost_Per_Cheese();
        unsigned int result = Cost_For_Type() + cost_for_salt + cost_for_cheese;

        return result;
    }

    void Print_Cost()
    {
        std::cout << Determine_Cost() << std::endl;
    }

    unsigned int Get_Total_Cost()
    {
        return Determine_Cost();
    }

};

class Detroit: public Pizza
{

    public:

    Detroit(PizzaSize _size, unsigned int _cheeseness, unsigned int _saltiness) : Pizza(_size, _cheeseness, _saltiness){};

    void Print_Description()
    {
        std::cout << "Tasty Detroit pizza" << std::endl;
    }

    unsigned int Cost_For_Type()
    {
        return 20*size;
    }

    unsigned int Cost_Per_Salt()
    {
        return 3;
    }

    unsigned int Cost_Per_Cheese()
    {
        return 3;
    }


};

class Margarita: public Pizza
{

    public:

    Margarita(PizzaSize _size, unsigned int _cheeseness, unsigned int _saltiness) : Pizza(_size, _cheeseness, _saltiness){};

    void Print_Description()
    {
        std::cout << "Beautifull Margarita pizza" << std::endl;
    }

    unsigned int Cost_For_Type()
    {
        return 30*size;
    }

    unsigned int Cost_Per_Salt()
    {
        return 4;
    }

    unsigned int Cost_Per_Cheese()
    {
        return 4;
    }

};

class Order
{
    std::vector<Pizza *> pizzas;

    public:

    void Add(Pizza *pizza)
    {
        pizzas.push_back(pizza);
    }

    void Print()
    {
        unsigned int total_order_cost = 0;
        int order_size = pizzas.size();
        for(int i = 0; i < order_size; i++)
        {
            pizzas[i]->Print_Description();
            unsigned int pizza_cost = pizzas[i]->Get_Total_Cost();
            std::cout << "Pizza cost: " << pizza_cost                     << std::endl;
            std::cout << "Cheeseness: " << pizzas[i]->Get_Cheeseness()    << std::endl;
            std::cout << "Saltiness: "  << pizzas[i]->Get_Saltiness()     << std::endl;
            std::cout << "Size: "       << pizzas[i]->Get_Size() << " cm" << std::endl;
            std::cout << std::endl;
            total_order_cost += pizza_cost;
        }
        std::cout << "Total cost for order: " << total_order_cost << std::endl;
    }

    void Interact()
    {
        std::cout << "Welcome to PizzaTown! Please, feel free to order something!" << std::endl;
        int running = 1;

OrderNewItem:
        while(running)
        {
            std::cout << "Here is our menu! If you want to order something, just type number of pizza (or 0, if you done with your order)." << std::endl;
            std::cout << "1. Margarita" << std::endl;
            std::cout << "2. Detroit" << std::endl;
            int choice;
            // TODO: feel bad for that, ask about this
            unsigned int pizza_type = 0;

            std::cin >> choice;
            switch(choice)
            {
                case 0:
                {
                    running = 0;
                    goto OrderNewItem;
                } break;
                case 1:
                case 2:
                {
                    pizza_type = choice;
                } break;
                default:
                {
                    std::cout << "Something went wrong! Be sure to choose pizzas that are in menu!" << std::endl;
                    goto OrderNewItem;
                } break;
            }

            PizzaSize pizza_size;
            std::cout << "Choose size (you can type 0, if you want to change you mind about and choose different pizza)." << std::endl;

ChooseSize:
            std::cout << "1. Small (25 cm)." << std::endl;
            std::cout << "2. Medium (30 cm)." << std::endl;
            std::cout << "3. Lagre (35 cm)." << std::endl;
            std::cout << "4. Very large (40 cm)." << std::endl;

            std::cin >> choice;
            switch(choice)
            {
                case 0:
                {
                    std::cout << "Okay! Returning to main menu!" << std::endl;
                    goto OrderNewItem;
                } break;
                case 1:
                {
                    pizza_size = SMALL;
                } break;
                case 2:
                {
                    pizza_size = MEDIUM;
                } break;
                case 3:
                {
                    pizza_size = LARGE;
                } break;
                case 4:
                {
                    pizza_size = VERY_LARGE;
                } break;
                default:
                {
                    std::cout << "Something went wrong! Be sure to choose correct size!" << std::endl;
                    goto ChooseSize;
                } break;
            }

            unsigned int cheese_num = 0;
            unsigned int salt_num = 0;
            std::cout << "Do you want to add additional cheese or salt? (As always, you can type 0 if you want different pizza)" << std::endl;

ChooseFillings:
            std::cout << "1. Add cheese." << std::endl;
            std::cout << "2. Add salt." << std::endl;
            std::cout << "3. Skip fillings." << std::endl;

            std::cin >> choice;
            switch(choice)
            {
                case 0:
                {
                    std::cout << "Okay! Returning to main menu!" << std::endl;
                    goto OrderNewItem;
                } break;
                case 1:
                {
                    std::cout << "How much cheese do you want?" << std::endl;
                    std::cin >> cheese_num;
                    while(cheese_num < 0)
                    {
                        std::cout << "Something went wrong! Have you tried to enter negative number? Try again and be positive!" << std::endl;
                        std::cin >> cheese_num;
                    }
                    goto ChooseFillings;
                } break;
                case 2:
                {
                    std::cout << "How much salt do you want?" << std::endl;
                    std::cin >> salt_num;
                    while(salt_num < 0)
                    {
                        std::cout << "Something went wrong! Have you tried to enter negative number? Try again and be positive!" << std::endl;
                        std::cin >> salt_num;
                    }
                    goto ChooseFillings;
                } break;
                case 3:
                {
                } break;
                default:
                {
                    std::cout << "Something went wrong! Currently we have no different filling! Choose from existing ones!" << std::endl;
                    goto ChooseFillings;
                } break;
            }

            std::cout << "Pizza was added to your order!" << std::endl;

            //TODO: another switch statement just because I have no type for pizza
            switch(pizza_type)
            {
                case 1:
                {
                    Add(new Margarita(pizza_size, cheese_num, salt_num));
                } break;
                case 2:
                {
                    Add(new Detroit(pizza_size, cheese_num, salt_num));
                } break;
            }
        }
    }
};

int main()
{
    Order order;
#if 0
    Margarita m(SMALL);
    m.Add_Cheese(1);
    m.Add_Salt(3);

    order.Add(&m);

    Detroit d(LARGE);
    d.Add_Cheese(2);
    d.Add_Salt(1);

    order.Add(&d);
#endif

    order.Interact();

    order.Print();

    return 0;
}



