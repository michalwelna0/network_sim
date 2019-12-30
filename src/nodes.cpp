#include "nodes.hpp"
std::map<IPackageReceiver*, double> ReceiverPreferences::preferences_={};

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {

    preferences_[r] =  0;

}