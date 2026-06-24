import { test, expect } from '@playwright/test';

test.describe('Visual Model Editing and Mutations', () => {
  test.beforeEach(async ({ page }) => {
    // Navigate to the editor
    await page.goto('/');
    await page.waitForSelector('.monaco-editor');
    // Expose browser logs to console
    page.on('console', msg => console.log('BROWSER LOG:', msg.text()));
    page.on('pageerror', err => console.error('BROWSER ERROR:', err.message));
  });

  test('should support adding parts, adding ports, and renaming parts', async ({ page }) => {
    // --- 1. Add Part 'pump' ---
    const partInput = page.locator('input[placeholder="Part name (e.g. pump)"]');
    await partInput.fill('pump');
    
    const addPartButton = page.locator('button:has-text("Add Part")');
    await addPartButton.click();

    // Verify the code in Monaco contains the newly created part pump
    await expect.poll(async () => {
      return await page.evaluate(() => {
        return (window as any).editor ? (window as any).editor.getValue() : '';
      });
    }, { timeout: 5000 }).toContain('part pump;');

    // --- 2. Add Port 'a' to 'pump' ---
    // Select the 'pump' node on the canvas
    const pumpNode = page.locator('.react-flow__node[data-id="pump"]');
    await pumpNode.click();

    // Verify the toolbar indicates pump is selected
    await expect(page.locator('code')).toHaveText('pump');

    // Fill the port name input and submit
    const portInput = page.locator('input[placeholder="Port name"]');
    await portInput.fill('a');

    const addPortButton = page.locator('button:has-text("Port")');
    await addPortButton.click();

    // Verify Monaco editor has wrapped pump and added the port 'a' correctly without syntax errors
    await expect.poll(async () => {
      return await page.evaluate(() => {
        return (window as any).editor ? (window as any).editor.getValue() : '';
      });
    }, { timeout: 5000 }).toContain('part pump {\n        port a;\n    }');

    // --- 3. Rename 'pump' to 'superpump' ---
    // Re-select the 'pump' node since selection resets after adding a port
    await pumpNode.click();

    // Click the Rename button to open the edit input
    const renameButton = page.locator('button:has-text("Rename")');
    await renameButton.click();

    // Fill the rename input
    const renameInput = page.locator('button:has-text("Save")').locator('xpath=../input');
    await renameInput.fill('superpump');

    const saveButton = page.locator('button:has-text("Save")');
    await saveButton.click();

    // Verify Monaco editor reflects the rename
    await expect.poll(async () => {
      const val = await page.evaluate(() => {
        return (window as any).editor ? (window as any).editor.getValue() : '';
      });
      return val;
    }, { timeout: 5000 }).toContain('part superpump {\n        port a;\n    }');

    // Verify that the old name pump is no longer there
    const editorValue = await page.evaluate(() => {
      return (window as any).editor ? (window as any).editor.getValue() : '';
    });
    expect(editorValue).not.toContain('part pump {');
  });
});
