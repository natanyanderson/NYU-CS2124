//Natanya Anderson
//
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//
// Musician class as provided to the students. Requires an Instrument class.
//

class Instrument {
public:
    virtual void makeSound() const = 0;
    virtual void play() const = 0;
    virtual void output(ostream& os) const = 0;
};
ostream& operator<<(ostream& os, const Instrument* instr) {
    if (instr) {
        instr->output(os);
    }
    return os;
}

void Instrument::makeSound() const {
    cout << "To make a sound... ";
}
class Brass:public Instrument {
public:
    Brass(unsigned brassSize): size(brassSize) {}
    virtual void makeSound() const override {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << size << endl;
    }
    virtual void output(ostream& os) const override {
        os << "Brass: " << size;
    }
protected:
    unsigned getSize() const { return size; }
private:
    unsigned size;
};
class Trumpet: public Brass {
public:
    Trumpet(unsigned size): Brass(size) {}
    virtual void play() const override {
        cout << "Toot";
    }
    virtual void output(ostream& os) const override {
        os << "Trumpet: " << getSize(); // Generic Brass output
    }
};
class Trombone: public Brass {
public:
    Trombone(unsigned size): Brass(size) {}
    virtual void play() const override {
        cout << "Blat";
    }
    virtual void output(ostream& os) const override {
        os << "Trombone: " << getSize(); // Generic Brass output
    }
};
class String: public Instrument{
public:
    String(unsigned stringPitch): pitch(stringPitch) {}
    virtual void makeSound() const override {
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    };
protected:
    unsigned getPitch() const { return pitch; }
private:
    unsigned pitch;
};
class Violin: public String{
public:
    Violin(unsigned violinPitch): String(violinPitch) {}
    virtual void play() const override {
        cout << "Screech";
    }
    virtual void output(ostream& os) const override {
        os << "Trombone: " << getPitch(); // Generic Brass output
    }
};
class Cello: public String {
public:
    Cello(unsigned celloPitch): String(celloPitch) {}
    virtual void play() const override {
        cout << "Squawk";
    }
    virtual void output(ostream& os) const override {
        os << "Celo: " << getPitch(); // Generic Brass output
    }
};

class Percussion: public Instrument {
public:
    virtual void makeSound() const override {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};
class Drum: public Percussion {
public:
    virtual void play() const override {
        cout << "Boom";
    }
    virtual void output(ostream& os) const override {
        os << "Drum";
    }
};
class Cymbal: public Percussion {
public:
    virtual void play() const override {
        cout << "Crash";
    }
    virtual void output(ostream& os) const override {
        os << "Cymbal";
    }
};
class MILL{
    friend ostream& operator<<(ostream& os, const MILL& mill) {
        bool hasInstruments = false;
        for (const Instrument* instr : mill.instruments) {
            if (instr != nullptr) {
                hasInstruments = true;
                break; // Found a valid instrument, no need to check further.
            }
        }
        if (!hasInstruments) { // If no instruments are found
            os << "The MILL has the following instruments: None";
        } else {
            os << "The MILL has the following instruments: \n";
            for (const Instrument* instr : mill.instruments) {
                if (instr != nullptr) {
                    os << "\t";
                    instr->output(os);
                    os << "\n";
                } else {
                    os << "None";
                    break;
                }
            }
        }
        return os;
    }
public:
    MILL(): instruments(0) {}
    void dailyTestPlay() {
        for(const Instrument* instr: instruments) {
            if (instr != nullptr) {
                instr->makeSound();
            }
        }
    }
    void receiveInstr(Instrument& instrument) {
        instrument.makeSound();
        Instrument* instr = &instrument;
        size_t instr_index = instruments.size();
        for(size_t index = 0; index < instruments.size(); index++) {
            if (instruments[index] == nullptr) {
                instruments[index] = instr;
                instr_index = index;
                break;
            }
        }
        if (instr_index == instruments.size()) {
            instruments.push_back(instr);
        }
    }
    Instrument* loanOut() {
        Instrument* instrument = nullptr;
        for (Instrument*& instr: instruments) {
            if (instr != nullptr) {
                instrument = instr;
                instr = nullptr;
                break;
            }
        }
        return instrument;
    }
private:
    vector<Instrument*> instruments;
};


class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) {
            instr->makeSound();
        }
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};

class Orch {
public:
    void addPlayer(Musician& musician) {
        musicians.push_back(&musician);
    }
    void play() const {
        for(size_t i = 0; i < musicians.size(); i++){
            musicians[i] -> play();
        }
        cout << endl;
    }
private:
    vector<Musician*> musicians;
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
     Drum drum;
     Cello cello(673);
     Cymbal cymbal;
     Trombone tbone(4);
     Trumpet trpt(12) ;
     Violin violin(567) ;

    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";

    cout << "Daily test ----------------------------------------------------\n"
         << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;

    cout << "Define some Musicians------------------------------------------\n";
     Musician harpo("Harpo");
     Musician groucho("Groucho");

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
     groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

     groucho.testPlay();
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     groucho.testPlay();
     harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
     mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
        mill.dailyTestPlay();

    cout << "\nThe MILL at the end of Part One:\n";
     cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";

    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;

}
