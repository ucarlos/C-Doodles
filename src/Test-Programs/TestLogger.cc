/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 08/23/2023 at 10:41 PM
 *
 * TestLogger.cc
 *
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include "../Logger.hpp"

int main(void) {
    Logger logger;
	logger.logger().set_level(spdlog::level::critical);
    logger.info("This is an example!");
    logger.info("This is another example!");

    logger.debug("This is a debug statement!");
    logger.warn("And this is a warn statement.");
    logger.error("This is an error statement");
    logger.critical("And this is a critical statement.");




}
