import { defineConfig, devices } from '@playwright/test';

export default defineConfig({
  testDir: './e2e',
  fullyParallel: false,
  forbidOnly: !!process.env.CI,
  retries: process.env.CI ? 2 : 0,
  workers: 1,
  reporter: 'line',
  use: {
    baseURL: 'http://localhost:5173',
    trace: 'on-first-retry',
    permissions: ['clipboard-read', 'clipboard-write'],
    headless: true,
  },
  projects: [
    {
      name: 'chromium',
      use: { ...devices['Desktop Chrome'] },
    },
  ],
  webServer: [
    {
      command: 'cargo run',
      cwd: '../backend',
      url: 'http://127.0.0.1:3000/',
      reuseExistingServer: true,
      stdout: 'pipe',
      stderr: 'pipe',
      timeout: 120000,
    },
    {
      command: 'npm run dev',
      url: 'http://localhost:5173',
      reuseExistingServer: true,
      stdout: 'pipe',
      stderr: 'pipe',
      timeout: 60000,
    }
  ],
});
