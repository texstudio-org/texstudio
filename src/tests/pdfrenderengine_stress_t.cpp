/***************************************************************************
 *   copyright       : (C) 2021 by Andreas Stöckel                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QT_NO_DEBUG

#include <pdfviewer/pdfrendermanager.h>

#include <QThread>
#include <QtTest/QtTest>
#include <iostream>
#include <random>

#include "pdfrenderengine_stress_t.h"

void PDFRenderEngineStressTest::test_multithreading()
{
	const size_t N_THREADS = 8; // Can trigger the bug more roboustly with 16
	const size_t N_IT = 100;
	const size_t N_REPEAT = 1000;

	std::default_random_engine re(5892190);  // Random engine with fixed seed
	std::uniform_int_distribution<int> dist_page(0, 20);

	for (size_t j = 0; j < N_REPEAT; j++) {
		PDFRenderManager manager(this, N_THREADS);
		PDFRenderManager::Error err = PDFRenderManager::NoError;

		// Fetch the test document here:
		// http://compneuro.uwaterloo.ca/files/publications/stoeckel.2020c.pdf
		manager.loadDocument("stoeckel.2020c.pdf", err, "");
		manager.setCacheSize(0);  // Keep nothing in the cache

		for (size_t i = 0; i < N_IT; i++) {
			std::cerr << "\rIteration " << (j * N_IT + i) << "/"
			          << (N_REPEAT * N_IT) << std::flush;

			// Submit a render job with no receiver object
			manager.renderToImage(dist_page(re), nullptr, "");

			// Process signal/slot events
			QCoreApplication::processEvents();
		}
	}
}

#endif  // QT_NO_DEBUG
