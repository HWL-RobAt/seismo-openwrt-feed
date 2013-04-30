/*
 * BlockMember.cpp
 *
 *  Created on: 09.04.2009
 *      Author: ingmar
 */

#include "BlockMember.h"

BlockMember::BlockMember() {
}

BlockMember::~BlockMember() {
}

void BlockMember::addBlockMember(std::string processName, RTDS_QueueId reference) {
	blockMember[processName] = reference;
}

RTDS_QueueId BlockMember::getBlockMember(std::string processName) {
  return blockMember[processName];
}
