#include <vector>
#include <algorithm>
#include <iostream>

#define NEW_TEMP(X) X * 0.9

class Knapsack;
class Item {    

  friend class Knapsack;
  private:
    float weight;
    float cost;
  
  public:
    Item() {
      weight = -1;
      cost = -1;
    }

    Item(float w, float c) {
      this->weight = w;
      this->cost = c;
    }

    bool operator== (const Item &o) { 
      return this->cost == o.cost && this->weight == o.weight; 
    };
};

class Knapsack {
  private:
    std::vector<Item> items;
    float capacity;

  public:
    Knapsack(float capacity) {
      this->items = std::vector<Item>();
      this->capacity = capacity;      
    };

    Knapsack(float capacity, std::vector<Item> items) {
      this->items = std::vector<Item>();
      this->capacity = capacity;   
      for (Item i : items) {
        this->items.push_back(i);
      }   
    };

    Knapsack (const Knapsack &k) {
      this->capacity = k.capacity;
      this->items = std::vector<Item>();
      for (Item i : k.items) {
        this->items.push_back(i);
      }
    };

    

    void addOrRemove(Item i) {
      std::vector<Item>::iterator _item = std::find(items.begin(), items.end(), i);
      if (_item == items.end()) {
        items.push_back(i);
      } else {
        items.erase(_item);
      }
    };

    float value() {
      float total_weight = 0;
      float total_cost = 0;

      for (Item i: items) {
        total_cost += i.cost;
        total_weight += i.weight;
      }

      if (total_weight > capacity) return -1;
      return total_cost;
    };

    float weight() {
      float total_weight = 0;
      for (Item i: items) {
        total_weight += i.weight;
      }
      return total_weight;
    };

    bool operator>(Knapsack k) {
      return this->value() > k.value();
    }

    float operator-(Knapsack k) {
      return this->value() - k.value();
    }
};

  std::ostream& operator<<(std::ostream &o, Knapsack &k) {
    o << "WEIGHT: " << (int)k.weight() <<  " VALUE: " << (int)k.value();
    return o;
  }