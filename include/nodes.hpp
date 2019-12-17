#ifndef NETWORK_SIM_NODES_HPP
#define NETWORK_SIM_NODES_HPP
#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include <memory>



enum class ReceiverType{
    Male, Female
};


class IPackageReceiver{
public:
    virtual void receive_package(Package&& p) = 0;
    virtual ReceiverType get_receiver_type() const = 0;
    virtual ElementID get_id() const =0;


};


class Storehouse : public IPackageReceiver{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d): id_(id), d_(std::move(d)) {}
    void receive_package (Package&& p) override;
    ReceiverType get_receiver_type() const override;
    ElementID get_id() const override;
private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;

};


class ReceiverPreferences{};
class PackageSender{};
class Ramp{};


class Worker : public IPackageReceiver{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)) {}
    void do_work();
    TimeOffset get_processing_duration() const;
    Time get_package_processing_start_time() const;
    void receive_package (Package&& p) override;
    ReceiverType get_receiver_type() const override;
    ElementID get_id() const override;

private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<PackageQueue> q_;


};
#endif //NETWORK_SIM_NODES_HPP
