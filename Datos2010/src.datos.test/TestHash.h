/*
 * TestHash.h
 *
 *  Created on: 01/05/2010
 *      Author: richy
 */

#ifndef TESTHASH_H_
#define TESTHASH_H_

class TestHash {
public:
	TestHash();
	virtual ~TestHash();
	void runCreateAndInsertTest();
	void runSearchTest();
	void runRemoveTest();
	void runUpdateTest();
	void runExampleCatedraTest();
	void runPrintTest();
	void runInsertFile();

};

#endif /* TESTHASH_H_ */
