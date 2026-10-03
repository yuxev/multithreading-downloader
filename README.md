<picture>
  <source media="(prefers-color-scheme: dark)" srcset="docs/banner-dark.svg" />
  <img src="docs/banner-light.svg" width="100%" alt="multithreading-downloader: Download many files in parallel: one std::thread and one libcurl handle per URL." />
</picture>

Built a multi-threaded C++ file downloader using libcurl to manage parallel downloads efficiently, ensuring data integrity with mutex synchronization and supporting custom download paths.

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="docs/flow-dark.svg" />
  <img src="docs/flow-light.svg" width="100%" alt="Main thread collects URLs, spawns one thread per URL, then joins them all" />
</picture>

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="docs/thread-dark.svg" />
  <img src="docs/thread-light.svg" width="100%" alt="Each thread: curl_easy_init, fopen, write callback, curl_easy_perform, cleanup" />
</picture>

## Run it

```bash
make                      # needs libcurl (e.g. apt install libcurl4-openssl-dev)
./monazil_almilafat
# paste URLs one per line, type D when done, then pick a folder (or press Enter)
```

<sub>Diagrams in <code>docs/</code> are generated SVGs, drawn to match the code in this repo.</sub>
