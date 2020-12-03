// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#ifndef MODBUSMANAGER_MODBUSNETWORK_OBSERVEBLE_H
#define MODBUSMANAGER_MODBUSNETWORK_OBSERVEBLE_H

/************************************************************
 Observeble class header
 ************************************************************/

#include "Observer.h"
#include "vector"

// Include from Include stereotype (header)
#include "Pkg_src.h"
// End of Include stereotype (header)


namespace src {

/************************************************************/
/**
 * <Observer Pattern>
 * 
 * Observeble Class
 * 
 * This class implement the necessary methos for a observable object.
 * The use of this class can e done by simple inheritance.
 */
class Observeble {
public:
	/**
	 * 
	 */
	std::vector<Observer*> observerCollection;
	/**
	 * 
	 */
	Observer *import;

	/**
	 * Notify all observers
	 */
	void notify();

	/**
	 * Construtor
	 */
	virtual ~Observeble();

	/**
	 * 
	 * @param observer 
	 */
	void add(Observer* /*in*/observer);

	/**
	 * 
	 * @param observer 
	 */
	void remove(Observer* /*in*/observer);

};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

} // of src

/************************************************************
 End of Observeble class header
 ************************************************************/

#endif
