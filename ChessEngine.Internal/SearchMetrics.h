#pragma once

#include <chrono>

#define METRICS_SET_MAX_DEPTH(check, metrics, maxDepth) if constexpr (check) { metrics.SetMaxDepth(maxDepth); }

#define METRICS_SEARCH_START(check, metrics) if constexpr (check) { metrics.SearchStart(); }
#define METRICS_SEARCH_STOP(check, metrics)  if constexpr (check) { metrics.SearchStop();  }
#define METRICS_SEARCH_INCREMENT(check, metrics, increment) if constexpr (check) { metrics.SearchIncrementPositions(increment); }

#define METRICS_GENERATION_START(check, metrics) if constexpr (check) { metrics.GenerationStart(); }
#define METRICS_GENERATION_STOP(check, metrics)  if constexpr (check) { metrics.GenerationStop();  }
#define METRICS_GENERATION_INCREMENT(check, metrics, increment) if constexpr (check) { metrics.GenerationIncrementPositions(increment); }

#define METRICS_EVALUATION_START(check, metrics) if constexpr (check) { metrics.EvaluationStart(); }
#define METRICS_EVALUATION_STOP(check, metrics)  if constexpr (check) { metrics.EvaluationStop();  }
#define METRICS_EVALUATION_INCREMENT(check, metrics, increment) if constexpr (check) { metrics.EvaluationIncrementPositions(increment); }

#define METRICS_PRINT(check, metrics) if constexpr (check) { metrics.PrintMetrics(); }
#define METRICS_WRITE(check, metrics) if constexpr (check) { metrics.WriteMetrics(); }

namespace ChessEngine
{
	// Mostly header defined, I'm hoping this means that this is all inlined and has negligable
	// performance impact so that the metrics collected are as accurate as possible.

	class SearchMetrics
	{
	public:

		// Set the max ply that the search is performed to
		void SetMaxDepth(const unsigned char maxDepth)
		{
			m_maxDepth = maxDepth;
		}

		// Start recording the time spent searching positions
		void SearchStart()
		{
			m_searchStart = std::chrono::system_clock::now();
		}

		// Stop recording the time spent searching positions, then add elapsed time to total
		void SearchStop()
		{
			m_searchStop = std::chrono::system_clock::now();
			m_searchTotalTime += (m_searchStop - m_searchStart);
		}

		// Increment the total number of positions searched
		void SearchIncrementPositions(int increment)
		{
			m_searchTotalPositions += increment;
		}

		// Get the total time spent searching positions (seconds)
		std::chrono::duration<double> GetSearchTotalTime() const
		{
			return m_searchTotalTime;
		}

		// Get the total number of positions searched
		int GetSearchTotalPositions() const
		{
			return m_searchTotalPositions;
		}

		// Start recording the time spent generating positions
		void GenerationStart()
		{ 
			m_generationStart = std::chrono::system_clock::now();
		}

		// Stop recording the time spent generating positions, then add elapsed time to total
		void GenerationStop()
		{
			m_generationStop = std::chrono::system_clock::now();
			m_generationTotalTime += (m_generationStop - m_generationStart);
		}

		// Increment the total number of positions generated 
		void GenerationIncrementPositions(int increment)
		{
			m_generationTotalPositions += increment;
		}

		// Get the total time spent generating positions (seconds)
		std::chrono::duration<double> GetGenerationTotalTime() const
		{ 
			return m_generationTotalTime;
		}

		// Get the total number of positions generated
		int GetGenerationTotalPositions() const 
		{
			return m_generationTotalPositions;
		}

		// Start recording the time spent evaluating positions
		void EvaluationStart()
		{
			m_evaluationStart = std::chrono::system_clock::now();
		}

		// Stop recording the time spent evaluating positions, then add elapsed time to total
		void EvaluationStop()
		{
			m_evaluationStop = std::chrono::system_clock::now();
			m_evaluationTotalTime += (m_evaluationStop - m_evaluationStart);
		}

		// Increment the total number of positions evaluated
		void EvaluationIncrementPositions(int increment)
		{
			m_evaluationTotalPositions += increment;
		}

		// Get the total time spent evaluating positions (seconds)
		std::chrono::duration<double> GetEvaluationTotalTime() const
		{
			return m_evaluationTotalTime;
		}

		// Get the total number of positions evaluated
		int GetEvaluationTotalPositions() const
		{
			return m_evaluationTotalPositions;
		}

		// Print a summary of the metrics to std::cout
		void PrintMetrics() const;

		// Write the metrics out as CSV
		void WriteMetrics() const;

	private:

		unsigned char m_maxDepth = 0; // The max depth the search is performed to

		std::chrono::time_point<std::chrono::system_clock> m_searchStart;
		std::chrono::time_point<std::chrono::system_clock> m_searchStop;
		std::chrono::duration<double> m_searchTotalTime{ 0.0 };					// The total time spend searching positions
		int m_searchTotalPositions = 0;											// The total number of positions searched (<= number of positions generated)

		std::chrono::time_point<std::chrono::system_clock> m_generationStart;
		std::chrono::time_point<std::chrono::system_clock> m_generationStop;
		std::chrono::duration<double> m_generationTotalTime{ 0.0 };				// The total time spent generating positions (seconds)
		int m_generationTotalPositions = 0;										// The total number of positions generated

		std::chrono::time_point<std::chrono::system_clock> m_evaluationStart;
		std::chrono::time_point<std::chrono::system_clock> m_evaluationStop;
		std::chrono::duration<double> m_evaluationTotalTime{ 0.0 };				// The total time spent evaluating nodes (seconds)
		int m_evaluationTotalPositions = 0;										// The total number of positions evaluated (<= number of positions searched)
	};
}
