#ifndef NETWORK_SIM_FACTORY_HPP
#define NETWORK_SIM_FACTORY_HPP
#include "types.hpp"
#include "nodes.hpp"

template <class Node>
class NodeCollection{
public:
    using list_t = typename std::list<Node>;
    using iterator = typename list_t::iterator;
    using const_iterator = typename list_t::const_iterator;

    iterator begin() const {return list_.begin();}
    iterator end() const {return list_.end();}

    const_iterator cbegin() const {return list_.cbegin();}
    const_iterator cend() const {return list_.cend();}

    iterator begin() {return list_.begin();}
    iterator end() {return list_.end();}

    void add(Node& node) {return list_.insert(std::move(node));}

    void remove_by_id(ElementID id_){auto ptr = find_by_id(id_); if(ptr!=list_.end()){list_.erase(ptr);}}

    NodeCollection<Node>::iterator find_by_id(ElementID id_) {return std::find_if(list_.begin(),list_.end(),
            [id_](const auto& elem){return (elem->get_id()==id_);});};

    NodeCollection<Node>::const_iterator find_by_id(ElementID id_)const {return std::find_if(list_.cbegin(),list_.cend(),
            [id_](const auto& elem){return (elem->get_id()==id_);});};


private:
    list_t list_;
};




class Factory{
    // dla klasy Ramp
public:
    void add_ramp(Ramp&& ramp){ramps.add(ramp);}
    void remove_ramp(ElementID id) {ramps.remove_by_id(id);}
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) {return ramps.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const {return ramps.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const {return ramps.cbegin();}
    NodeCollection<Ramp>::const_iterator ramp_cend() const {return ramps.cend();}

    void add_worker(Worker&& worker){workers.add(worker);}
    void remove_worker(ElementID id) {workers.remove_by_id(id);}
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) {return workers.find_by_id(id);}
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const {return workers.find_by_id(id);}
    NodeCollection<Worker>::const_iterator worker_cbegin() const {return workers.cbegin();}
    NodeCollection<Worker>::const_iterator worker_cend() const {return workers.cend();}

    void add_storehouse(Storehouse&& storehouse){storehouses.add(storehouse);}
    void remove_storehouse(ElementID id) {storehouses.remove_by_id(id);}
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) {return storehouses.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const {return storehouses.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const {return storehouses.cbegin();}
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const {return storehouses.cend();}

    bool is_consistent() const;
    void do_deliveries(Time t) {std::for_each(ramps.begin(),ramps.end(),[t](auto buff){buff->deliver_goods(t);});}
    void do_package_passing();
    void do_work(Time t) {std::for_each(workers.begin(),workers.end(), [t](auto buff){buff->deliver_goods(t);});}


private:
    NodeCollection<Ramp> ramps;
    NodeCollection<Worker> workers;
    NodeCollection<Storehouse> storehouses;






};



#endif //NETWORK_SIM_FACTORY_HPP
