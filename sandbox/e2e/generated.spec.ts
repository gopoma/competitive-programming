require("dotenv").config();

import { test, expect as baseExpect } from '@playwright/test';

// expect.configure carries the configured timeout into every assertion AND expect.poll,
// without annotating each one. Shadows the imported expect for this spec.
const expect = baseExpect.configure({ timeout: 15000 });

async function waitForEphemeralEmail(tag, since, timeoutMs) {
  const apiKey = process.env.TESTMAIL_API_KEY;
  const namespace = process.env.TESTMAIL_NAMESPACE;
  if (!apiKey || !namespace) throw new Error('Set TESTMAIL_API_KEY and TESTMAIL_NAMESPACE.');
  const deadline = Date.now() + timeoutMs;
  while (Date.now() < deadline) {
    const params = new URLSearchParams({ apikey: apiKey, namespace, tag, timestamp_from: String(since), limit: '5' });
    try {
      const res = await fetch(`https://api.testmail.app/api/json?${params}`, { headers: { accept: 'application/json' } });
      if (res.ok) {
        const payload = await res.json();
        const email = (payload.emails || []).slice().sort((a, b) => (Number(b.timestamp) || 0) - (Number(a.timestamp) || 0))[0];
        if (payload.result === 'success' && email) return email;
      }
    } catch (_) {}
    await new Promise((r) => setTimeout(r, 10000));
  }
  throw new Error(`Timed out waiting for the ephemeral email (tag ${tag}).`);
}
test.use({
  viewport: {
    width: 1920,
    height: 1080,
  },
  ignoreHTTPSErrors: true,
  permissions: ['clipboard-read', 'clipboard-write'],
  actionTimeout: 20000,
  navigationTimeout: 60000,
  video: {
    mode: 'on',
    size: { width: 1920, height: 1080 },
  },
  launchOptions: {
    headless: true,
    slowMo: 300,
    args: [
      '--no-sandbox',
      '--disable-gpu',
      '--disable-dev-shm-usage',
      '--disable-dev-tools',
      '--no-zygote',
    ],
  },
});

test.setTimeout(300000);

test('generated hybrid pipeline test de73647e8f7e422785606486f76b521f', async ({ page }) => {
  page.setDefaultTimeout(20000);
  page.setDefaultNavigationTimeout(60000);
  const randomDigits = String(Math.floor(Math.random() * 1e8)).padStart(8, '0');
  const tag = `nmv${Date.now().toString(36)}${Math.random().toString(36).slice(2, 6)}`;
  const email = `${process.env.TESTMAIL_NAMESPACE}.${tag}@inbox.testmail.app`;
  const emailSearchStart = Date.now();
  await test.step("1. Navigate to...", async () => {
    await page.goto("https://nmviajes.com/resultados?rand=4378718217&departureLocation=TCQ%20Tacna,%20Peru&arrivalLocation=CIX%20Chiclayo,%20Peru&departureDate=30%2F06%2F2026&arrivalDate=&adults=1&children=0&infants=0&flightType=1&flightClass=0&lang=ES&email=", { waitUntil: 'domcontentloaded' });
  });
  await test.step("2. Accepting cookies to clear the banner and ensure it doesn't interfere with subsequent actions.", async () => {
    await page.getByRole("button", { name: "Aceptar cookies", exact: true }).click();
  });
  await test.step("3. Clicking the 'Comprar' button associated with the 'MEJOR OPCIÓN' flight.", async () => {
    await page.getByRole("button", { name: "Comprar", exact: true }).nth(0).click();
  });
  await test.step("4. Choosing the 'Basic' plan by clicking its 'Seleccionar' button within the active modal.", async () => {
    await page.locator("ngb-modal-window[role=\"dialog\"]").getByRole("button", { name: "Seleccionar", exact: true }).nth(0).click();
  });
  await test.step("5. Filling the 'Información de pasajeros' form using the fill_form skill.", async () => {
    await page.locator("div#ngb-panel-ADT-0-collapse > div > form").getByRole("combobox", { name: "Tipo de documento *", exact: true }).selectOption({ label: "DNI" });
    await page.locator("div#ngb-panel-ADT-0-collapse > div > form").getByRole("textbox", { name: "Nombres *", exact: true }).fill("Bryan Orlando");
    await page.locator("div#ngb-panel-ADT-0-collapse > div > form").getByRole("textbox", { name: "Apellidos *", exact: true }).fill("Hancco Condori");
    await page.locator("select#ADT-0-day").selectOption({ label: "28" });
    await page.locator("select#ADT-0-month").selectOption({ label: "Julio" });
    await page.locator("select#ADT-0-year").selectOption({ label: "2004" });
    await page.locator("div#ngb-panel-ADT-0-collapse > div > form").getByRole("combobox", { name: "Nacionalidad *", exact: true }).fill("ESPA\u00d1A");
  });
  await test.step("6. Confirming the 'Nacionalidad' selection by clicking the suggested option.", async () => {
    await page.locator("ngb-typeahead-window#ngb-typeahead-0").getByRole("option", { name: "ESPA\u00d1A", exact: true }).click();
  });
  await test.step("7. Selecting 'Masculino' for the 'Genero' field using the native select element.", async () => {
    await page.locator("div#ngb-panel-ADT-0-collapse > div > form").getByRole("combobox", { name: "G\u00e9nero *", exact: true }).selectOption({ label: "Masculino" });
  });
  await test.step("8. Selecting 'DNI' for 'Tipo de documento'.", async () => {
    await page.locator("div#ngb-panel-ADT-0-collapse > div > form").getByRole("combobox", { name: "Tipo de documento *", exact: true }).selectOption({ label: "DNI" });
  });
  await test.step("9. Filling the 'DNI' field with a random 8-digit number.", async () => {
    await page.locator("div#ngb-panel-ADT-0-collapse > div > form").getByPlaceholder("Ingresar documento", { exact: true }).fill(randomDigits);
  });
  await test.step("10. Waiting for the 'Guardar' button to become enabled after filling the DNI field.", async () => {
    await page.locator("div:nth-of-type(3) > app-button > button[type=\"submit\"]").waitFor({ state: "visible" });
  });
  await test.step("11. The 'Guardar' button is now enabled, so I can proceed to click it to save the passenger information.", async () => {
    await page.locator("div#ngb-panel-ADT-0-collapse > div > form").getByRole("button", { name: "Guardar", exact: true }).click();
  });
  await test.step("12. Filling the 'Envío de información de vuelo' form with the provided details.", async () => {
    await page.getByRole("textbox", { name: "Nombre *", exact: true }).fill("Diego");
    await page.getByRole("textbox", { name: "Apellidos *", exact: true }).fill("Huamani Luque");
    await page.getByRole("textbox", { name: "C\u00f3digo *", exact: true }).fill("+51");
    await page.getByRole("textbox", { name: "N\u00famero de tel\u00e9fono *", exact: true }).fill("999999999");
    await page.getByRole("textbox", { name: "Correo electr\u00f3nico *", exact: true }).fill(email);
  });
  await test.step("13. Choosing 'Pago en efectivo / Banca por internet' as the payment method.", async () => {
    await page.locator("article > form").getByRole("radio", { name: "Pago en efectivo / Banca por internet", exact: true }).click();
  });
  await test.step("14. Checking the 'He leído y aceptado...' checkbox.", async () => {
    await page.getByRole("checkbox", { name: "He le\u00eddo y aceptado la pol\u00edtica de protecci\u00f3n de datos personales , los t\u00e9rminos y condiciones de compra y documentaci\u00f3n de viaje.", exact: true }).check();
  });
  await test.step("15. Clicking the 'Realizar Compra' button to finalize the purchase.", async () => {
    await page.locator("app-booking-process-page > form").getByRole("button", { name: "Realizar compra", exact: true }).click({ force: true });
  });
  await test.step("16. Waiting for 40 seconds as requested by the user.", async () => {
    await page.waitForTimeout(40000);
  });
  await test.step("17. Verify that the payment instructions page includes 'Banca por internet' as per step 11 of the user...", async () => {
    await expect(page.getByText("Banca por Internet").first()).toBeVisible();
  });
  await test.step("18. Verify that the email received includes 'SafetyPay' as per step 12 of the user request.", async () => {
    const received = await waitForEphemeralEmail(tag, emailSearchStart, 120000);
    const __mailHaystack = `${received.from ?? ""} ${received.subject ?? ""} ${received.text ?? received.html ?? ""}`.toLowerCase();
    expect(__mailHaystack).toMatch(new RegExp("safetypay"));
  });
});
