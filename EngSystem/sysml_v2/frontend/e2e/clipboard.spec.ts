import { test, expect } from '@playwright/test';

test.describe('Vim Mode Clipboard Sync', () => {
  test.beforeEach(async ({ page }) => {
    page.on('console', msg => console.log('PAGE LOG:', msg.text()));
    page.on('pageerror', err => console.error('PAGE ERROR:', err.message));
    // Navigate to the frontend page
    await page.goto('/');
    // Wait for editor to load
    await page.waitForSelector('.monaco-editor');
  });

  test('should paste from system clipboard into Vim buffer when pressing "p"', async ({ page, context }) => {
    // 1. Grant clipboard permissions
    await context.grantPermissions(['clipboard-read', 'clipboard-write']);

    // 2. Ensure Vim Mode is enabled
    const vimCheckbox = page.locator('label:has-text("Vim Mode") input[type="checkbox"]');
    const isChecked = await vimCheckbox.isChecked();
    if (!isChecked) {
      await vimCheckbox.click();
    }
    
    // Wait a brief moment for monaco-vim to initialize
    await page.waitForTimeout(500);

    // 3. Write a unique string to the system clipboard
    const testString = 'CLIPBOARD_PASTE_TEST_VALUE_' + Math.random().toString(36).substring(7);
    await page.evaluate((text) => navigator.clipboard.writeText(text), testString);

    // 4. Focus the editor and ensure we are in normal mode
    const textarea = page.locator('.monaco-editor textarea');
    await textarea.focus();
    await page.keyboard.press('Escape');
    
    // Trigger editor focus event to run the focus sync listener
    await page.evaluate(() => {
      if ((window as any).editor) {
        (window as any).editor.focus();
      }
    });
    
    // Give focus sync a moment to register
    await page.waitForTimeout(200);

    // 5. Press 'p' to paste in Vim normal mode
    await page.keyboard.press('p');

    // 6. Assert that the editor value contains our clipboard string
    const editorValue = await page.evaluate(() => {
      return (window as any).editor ? (window as any).editor.getValue() : '';
    });
    
    expect(editorValue).toContain(testString);
  });

  test('should copy Vim yanked text to system clipboard', async ({ page, context }) => {
    // 1. Grant clipboard permissions
    await context.grantPermissions(['clipboard-read', 'clipboard-write']);

    // 2. Ensure Vim Mode is enabled
    const vimCheckbox = page.locator('label:has-text("Vim Mode") input[type="checkbox"]');
    const isChecked = await vimCheckbox.isChecked();
    if (!isChecked) {
      await vimCheckbox.click();
    }
    
    // Wait a brief moment for monaco-vim to initialize
    await page.waitForTimeout(500);

    // 3. Set a specific value in the editor for testing
    const testString = 'YANK_TEST_VALUE_' + Math.random().toString(36).substring(7);
    await page.evaluate((text) => {
      if ((window as any).editor) {
        (window as any).editor.setValue(text);
      }
    }, testString);

    // 4. Focus the editor, enter normal mode, select all, and yank
    const textarea = page.locator('.monaco-editor textarea');
    await textarea.focus();
    await page.keyboard.press('Escape');
    
    // Move cursor to start
    await page.keyboard.press('g');
    await page.keyboard.press('g');
    
    // Yank line (yy)
    await page.keyboard.press('y');
    await page.keyboard.press('y');

    // 5. Read the system clipboard
    const clipboardText = await page.evaluate(() => navigator.clipboard.readText());

    // 6. Assert the clipboard text contains our editor value
    expect(clipboardText.trim()).toBe(testString);
  });

  test('should sync clipboard after window blur and focus transition', async ({ page, context }) => {
    // 1. Grant clipboard permissions
    await context.grantPermissions(['clipboard-read', 'clipboard-write']);

    // 2. Ensure Vim Mode is enabled
    const vimCheckbox = page.locator('label:has-text("Vim Mode") input[type="checkbox"]');
    const isChecked = await vimCheckbox.isChecked();
    if (!isChecked) {
      await vimCheckbox.click();
    }
    await page.waitForTimeout(500);

    // 3. Clear text first
    await page.evaluate(() => {
      if ((window as any).editor) {
        (window as any).editor.setValue('');
      }
    });

    // 4. Blur the window programmatically
    await page.evaluate(() => {
      window.dispatchEvent(new Event('blur'));
    });
    await page.waitForTimeout(100);

    // 5. Copy text to system clipboard outside of active window focus
    const transitionString = 'TRANSITION_TEST_VALUE_999';
    await page.evaluate((text) => navigator.clipboard.writeText(text), transitionString);

    // 6. Focus window and Monaco text area again
    await page.evaluate(() => {
      window.dispatchEvent(new Event('focus'));
      if ((window as any).editor) {
        (window as any).editor.focus();
      }
    });
    
    // Wait for the 100ms sync delay in App.tsx to complete
    await page.waitForTimeout(200);

    // 7. Focus Monaco editor textarea and press 'p' in normal mode
    const textarea = page.locator('.monaco-editor textarea');
    await textarea.focus();
    await page.keyboard.press('Escape');
    await page.keyboard.press('p');

    // 8. Assert that the editor value contains the transition string
    const editorValue = await page.evaluate(() => {
      return (window as any).editor ? (window as any).editor.getValue() : '';
    });
    expect(editorValue).toContain(transitionString);
  });

  test('should paste from clipboard when page loads with Vim Mode already enabled', async ({ page, context }) => {
    // 1. Grant clipboard permissions
    await context.grantPermissions(['clipboard-read', 'clipboard-write']);

    // 2. Set localStorage to have Vim mode enabled on page init
    await page.addInitScript(() => {
      window.localStorage.setItem('vim_mode_enabled', 'true');
    });

    await page.goto('/');
    await page.waitForSelector('.monaco-editor');
    await page.waitForTimeout(500);

    // 3. Write a unique string to system clipboard
    const testString = 'LOAD_ENABLED_TEST_VALUE_123';
    await page.evaluate((text) => navigator.clipboard.writeText(text), testString);

    // 4. Focus editor and trigger window focus event programmatically
    const textarea = page.locator('.monaco-editor textarea');
    await textarea.focus();
    await page.evaluate(() => {
      window.dispatchEvent(new Event('focus'));
      if ((window as any).editor) {
        (window as any).editor.focus();
      }
    });

    // Wait for the 100ms delay in App.tsx focus handler
    await page.waitForTimeout(200);

    // 5. Press 'p' to paste in Vim normal mode
    await page.keyboard.press('Escape');
    await page.keyboard.press('p');

    // 6. Assert editor value contains the pasted string
    const editorValue = await page.evaluate(() => {
      return (window as any).editor ? (window as any).editor.getValue() : '';
    });
    
    expect(editorValue).toContain(testString);
  });
});
