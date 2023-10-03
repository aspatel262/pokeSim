#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>

#include "Pokemon.hpp"
#include "Trainer.hpp"

using namespace std;

class League {
private:
  // TODO: Add member variables here
  int num_wins;
  int num_battles;
  vector<Trainer*> trainers;
  vector<Trainer*> defeated;
  int num_trainers;

public:

  // TODO: Add constructor here to initialize members
  League(istream &ash, istream &gym) {
    trainers.push_back(Trainer_factory(ash));
    string skip;
    gym >> num_trainers >> skip;
    for (int i = 0; i < num_trainers; i++) {
      trainers.push_back(Trainer_factory(gym));
    }
    num_wins = 0;
    num_battles = 0;
  }

  // TODO: Add member functions here
  void simulate() {
    for (int i = 1; i < num_trainers+1; i++) {
      trainers[0]->reset();
      cout << "-----" << *trainers[0] << " vs. " << *trainers[i] << "-----" << endl;
      this->battleSim(trainers[0], trainers[i]);
    }
    this->summarize();
  }

  void battleSim(Trainer *ash, Trainer *gym) {
    int num_wins = 0;
    for(int i = 0; i < 5; ++i) {
      num_wins += this->doBattle(i, ash, gym);
    }
    cout << "Result: " << *ash << "=" << num_wins << ", "
         << *gym << "=" << 5 - num_wins << endl;

    if (num_wins >= 3) {
      defeated.push_back(gym);
    }

    if (num_wins == 0 || num_wins == 5) {
      cout << "It's a clean sweep!" << endl;
    }

    cout << endl;
  }
  
  int doBattle(int pokNum, Trainer *ash, Trainer *gym) {
    int win = 0;
    Pokemon enemy = gym->choose_pokemon();
    cout << *gym << " chooses " << enemy << endl;
    Pokemon p = ash->choose_pokemon(enemy.get_type());
    cout << *ash << " chooses " << p << endl;
    if (Pokemon_battle(p, enemy)) {
      cout << p << " defeats " << enemy << endl << endl;
      ++win;
          }
    else {
      cout << enemy << " defeats " << p << endl << endl;
    }
    return win;
  }

  void summarize() {
    cout << *trainers[0] << " won " << defeated.size() << " matches by defeating:" << endl;
    for(int i = 0; i < defeated.size(); ++i) {
      cout << *defeated[i] << endl;
    }
  }

  ~League() {
    // TODO: put code here to clean up by deleting all Trainer objects
    for(size_t i = 0; i < trainers.size(); ++i) {
      delete trainers[i];
    }
  }
  
};

int main(int argc, char *argv[]) {

  // TODO: Add code to read command line args and open file streams here
  if (argc != 3) {
    cout << "Usage: battle.exe PLAYER_FILE GYM_LEADERS_FILE" << endl;
    return 1;
  }

  ifstream player_in(argv[1]);
  ifstream gym_in(argv[2]);
  if ( !player_in.is_open() ) {
    cout << "Unable to open " << argv[1] << endl;
    return 1;
  }

  if ( !gym_in.is_open() ) {
    cout << "Unable to open " << argv[2] << endl;
    return 1;
  }


  // TODO: Create a League object, call function to run the simulation
  League gym(player_in, gym_in);
  gym.simulate();


  
}